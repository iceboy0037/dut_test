#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

#include "cs104_slave.h"
#include "hal_thread.h"
#include "hal_time.h"

#include "dbg.h"
#include "yc.h"
#include "yc.h"
#include "rdb.h"

static bool running = true;
void sigint_handler(int signalId){
	running = false;
}
void printCP56Time2a(CP56Time2a time)
{
	println("%02i:%02i:%02i %02i/%02i/%04i", CP56Time2a_getHour(time),
	       CP56Time2a_getMinute(time),
	       CP56Time2a_getSecond(time),
	       CP56Time2a_getDayOfMonth(time),
	       CP56Time2a_getMonth(time),
	       CP56Time2a_getYear(time) + 2000);
}

/* Callback handler to log sent or received messages (optional) */
static void rawMessageHandler(void *parameter, IMasterConnection conneciton, uint8_t *msg, int msgSize, bool sent)
{
	if (sent) {
		println("SEND: ");
	} else {
		println("RCVD: ");
	}

	for (int i = 0; i < msgSize; i++) {
		println("%02x ", msg[i]);
	}
	println("\n");
}

static bool clockSyncHandler(void *parameter, IMasterConnection connection, CS101_ASDU asdu, CP56Time2a newTime)
{
	printCP56Time2a(newTime);
	println("\n");
	uint64_t newSystemTimeInMs = CP56Time2a_toMsTimestamp(newTime);

	println("Timestamp: %lu\n", newSystemTimeInMs);
	/* Set time for ACT_CON message */
	CP56Time2a_setFromMsTimestamp(newTime, Hal_getTimeInMs());
	/* update system time here */
	return true;
}

static bool interrogationHandler(void *parameter, IMasterConnection connection, CS101_ASDU asdu, uint8_t qoi)
{
	if (qoi == 20) { /* only handle station interrogation */
		CS101_AppLayerParameters alParams = IMasterConnection_getApplicationLayerParameters(connection);
		IMasterConnection_sendACT_CON(connection, asdu, false);

		/* The CS101 specification only allows information objects without timestamp in GI responses */
		CS101_ASDU newAsdu = CS101_ASDU_create(alParams, false, CS101_COT_INTERROGATED_BY_STATION, 0, 1, false, false);
		InformationObject io;
		for (int i = 0; i < 6; i++) {
			int value;
			if (yc_read_single(&value, i + 1) == 0) {
				io = (InformationObject)MeasuredValueScaled_create(NULL, 0x4001 + i, value, IEC60870_QUALITY_GOOD);
				CS101_ASDU_addInformationObject(newAsdu, io);
			}
		}
		InformationObject_destroy(io);
		IMasterConnection_sendASDU(connection, newAsdu);
		CS101_ASDU_destroy(newAsdu);

		newAsdu = CS101_ASDU_create(alParams, false, CS101_COT_INTERROGATED_BY_STATION, 0, 1, false, false);
		io = (InformationObject) SinglePointInformation_create(NULL, 104, true, IEC60870_QUALITY_GOOD);
		CS101_ASDU_addInformationObject(newAsdu, io);
		CS101_ASDU_addInformationObject(newAsdu, (InformationObject)
						SinglePointInformation_create((SinglePointInformation) io, 105, false, IEC60870_QUALITY_GOOD));
		InformationObject_destroy(io);
		IMasterConnection_sendASDU(connection, newAsdu);
		CS101_ASDU_destroy(newAsdu);

		newAsdu = CS101_ASDU_create(alParams, true, CS101_COT_INTERROGATED_BY_STATION, 0, 1, false, false);
		for (int i = 0; i < 12; i++) {
			char yx;
			if (yx_read_single(&yx, 0x80001 + i,  NULL) == 0) {
				io = (InformationObject) SinglePointInformation_create(NULL, i + 1, yx ? true : false, IEC60870_QUALITY_GOOD);
				CS101_ASDU_addInformationObject(newAsdu, io);
			}
		}
		InformationObject_destroy(io);
		IMasterConnection_sendASDU(connection, newAsdu);
		CS101_ASDU_destroy(newAsdu);

		newAsdu = CS101_ASDU_create(alParams, false, CS101_COT_INTERROGATED_BY_STATION, 0, 1, false, false);
		io = (InformationObject) BitString32_create(NULL, 500, 0xaaaa);
		CS101_ASDU_addInformationObject(newAsdu, io);
		InformationObject_destroy(io);
		IMasterConnection_sendASDU(connection, newAsdu);

		CS101_ASDU_destroy(newAsdu);
		IMasterConnection_sendACT_TERM(connection, asdu);
	} else {
		IMasterConnection_sendACT_CON(connection, asdu, true);
	}

	return true;
}

static bool asduHandler(void *parameter, IMasterConnection connection, CS101_ASDU asdu)
{
	if (CS101_ASDU_getTypeID(asdu) == C_SC_NA_1) {
		if (CS101_ASDU_getCOT(asdu) == CS101_COT_ACTIVATION) {
			InformationObject io = CS101_ASDU_getElement(asdu, 0);
			if (InformationObject_getObjectAddress(io) == 5000) {
				SingleCommand sc = (SingleCommand) io;
				println("IOA: %i switch to %i\n", InformationObject_getObjectAddress(io),
				       SingleCommand_getState(sc));
				CS101_ASDU_setCOT(asdu, CS101_COT_ACTIVATION_CON);
			} else {
				CS101_ASDU_setCOT(asdu, CS101_COT_UNKNOWN_IOA);
			}

			InformationObject_destroy(io);
		} else {
			CS101_ASDU_setCOT(asdu, CS101_COT_UNKNOWN_COT);
		}
		IMasterConnection_sendASDU(connection, asdu);
		return true;
	}

	return false;
}

static bool connectionReadHandler(void *parameter, IMasterConnection connection, CS101_ASDU asdu, int ioa)
{
	dbg("ioa = %d, %s\n", ioa, (char *)parameter);
	return true;
}

static bool connectionRequestHandler(void *parameter, const char *ipAddress)
{
	println("New connection request from %s\n", ipAddress);
#if 0

	if (strcmp(ipAddress, "127.0.0.1") == 0) {
		println("Accept connection\n");
		return true;
	} else {
		println("Deny connection\n");
		return false;
	}

#else
	return true;
#endif
}

static void connectionEventHandler(void *parameter, IMasterConnection con, CS104_PeerConnectionEvent event)
{
	if (event == CS104_CON_EVENT_CONNECTION_OPENED) {
		println("Connection opened (%p)\n", con);
	} else if (event == CS104_CON_EVENT_CONNECTION_CLOSED) {
		println("Connection closed (%p)\n", con);
	} else if (event == CS104_CON_EVENT_ACTIVATED) {
		println("Connection activated (%p)\n", con);
	} else if (event == CS104_CON_EVENT_DEACTIVATED) {
		println("Connection deactivated (%p)\n", con);
	}
}

int main(int argc, char **argv)
{
	rdb_init();
	/* Add Ctrl-C handler */
	signal(SIGINT, sigint_handler);
	/* create a new slave/server instance with default connection parameters and
	 * default message queue size */
	CS104_Slave slave = CS104_Slave_create(10, 10);
	CS104_Slave_setLocalAddress(slave, "192.168.56.200");
	/* Set mode to a single redundancy group
	 * NOTE: library has to be compiled with CONFIG_CS104_SUPPORT_SERVER_MODE_SINGLE_REDUNDANCY_GROUP enabled (=1)
	 */
	CS104_Slave_setServerMode(slave, CS104_MODE_SINGLE_REDUNDANCY_GROUP);
	/* get the connection parameters - we need them to create correct ASDUs -
	 * you can also modify the parameters here when default parameters are not to be used */
	CS101_AppLayerParameters alParams = CS104_Slave_getAppLayerParameters(slave);
	/* when you have to tweak the APCI parameters (t0-t3, k, w) you can access them here */
	CS104_APCIParameters apciParams = CS104_Slave_getConnectionParameters(slave);
	println("APCI parameters:\n");
	println("  t0: %i\n", apciParams->t0);
	println("  t1: %i\n", apciParams->t1);
	println("  t2: %i\n", apciParams->t2);
	println("  t3: %i\n", apciParams->t3);
	println("  k: %i\n", apciParams->k);
	println("  w: %i\n", apciParams->w);
	/* set the callback handler for the clock synchronization command */
	CS104_Slave_setClockSyncHandler(slave, clockSyncHandler, NULL);
	/* set the callback handler for the interrogation command */
	CS104_Slave_setInterrogationHandler(slave, interrogationHandler, NULL);
	/* set handler for other message types */
	CS104_Slave_setASDUHandler(slave, asduHandler, NULL);
	/* set handler to handle connection requests (optional) */
	CS104_Slave_setConnectionRequestHandler(slave, connectionRequestHandler, NULL);
	/* set handler to track connection events (optional) */
	CS104_Slave_setConnectionEventHandler(slave, connectionEventHandler, NULL);
	/* uncomment to log messages */
	CS104_Slave_setRawMessageHandler(slave, rawMessageHandler, NULL);

	//
	CS104_Slave_setReadHandler(slave, connectionReadHandler, "Parame");
	CS104_Slave_start(slave);

	if (CS104_Slave_isRunning(slave) == false) {
		println("Starting server failed!\n");
		goto exit_program;
	}

	int16_t scaledValue = 0;
	while (running) {
		Thread_sleep(1000);
		CS101_ASDU newAsdu = CS101_ASDU_create(alParams, false, CS101_COT_PERIODIC, 0, 1, false, false);
		InformationObject io = (InformationObject) MeasuredValueScaled_create(NULL, 110, scaledValue, IEC60870_QUALITY_GOOD);
		scaledValue++;
		CS101_ASDU_addInformationObject(newAsdu, io);
		InformationObject_destroy(io);
		/* Add ASDU to slave event queue */
		CS104_Slave_enqueueASDU(slave, newAsdu);
		CS101_ASDU_destroy(newAsdu);
	}
	CS104_Slave_stop(slave);

exit_program:
	CS104_Slave_destroy(slave);
	Thread_sleep(500);
}

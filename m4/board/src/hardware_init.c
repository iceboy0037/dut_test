/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "board.h"
#include "pin_mux.h"

void hardware_init(void)
{
	/* Board specific RDC settings */
	BOARD_RdcInit();
	/* Board specific clock settings */
	BOARD_ClockInit();
	/* initialize debug uart */
	dbg_uart_init();
	/* RDC MU*/
	RDC_SetPdapAccess(RDC, BOARD_MU_RDC_PDAP, 3 << (BOARD_DOMAIN_ID * 2), false, false);
	/* RDC EPITB */
	RDC_SetPdapAccess(RDC, BOARD_EPITB_RDC_PDAP, 3 << (BOARD_DOMAIN_ID * 2), false, false);
	/* Select EPIT clock derived from OSC 24M */
	CCM_SetRootMux(CCM, BOARD_EPIT_CCM_ROOT, ccmRootmuxPerclkClkOsc24m);
	/* Set relevant divider = 1. */
	CCM_SetRootDivider(CCM, BOARD_EPIT_CCM_DIV, 0);
	/* Enable clock used by EPITB */
	CCM_ControlGate(CCM, BOARD_EPITB_CCM_CCGR, ccmClockNeededAll);
	/* In this demo, we need to share SEMA4 access between domains */
	RDC_SetPdapAccess(RDC, BOARD_SEMA4_RDC_PDAP, 0xFF, false, false);
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
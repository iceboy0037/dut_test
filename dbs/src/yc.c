/**
 * @file yc.c
 * @brief yc
 * @author rock (gllier@163.com)
 * @version 1.0
 * @date 2020-12-19
 * @copyright Copyright (c) 2020 - 2020 Nanjing GWDR Power Technology Co., Ltd.
 * @par History:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2020-12-19 <td>1.0     <td>rock     <td>Create
 * </table>
 */

#include "dtu.h"
#include "yc.h"
#include "dbs.h"
#include "tables.h"

PT_MAP_START(yc)
	PT_ITEM("ua1",		PT_TYPE_FLOAT,	struct yc_table_t, 	bus[0].ua.raw)
	PT_ITEM("ub1",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("uc1",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("uab1",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ubc1",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("uca1",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("uz1",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("f1",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ua2",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ub2",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("uc2",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("uab2",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ubc2",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("uca2",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("uz2",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("f2",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ia1",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ia1",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ia1",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ia1",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ib1",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ic1",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("iz1",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p1",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q1",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s1",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos1",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ia2",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ib2",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ic2",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("iz2",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p2",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q2",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s2",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos2",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ia3",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ib3",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ic3",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("iz3",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p3",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q3",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s3",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos3",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ia4",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ib4",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ic4",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("iz4",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p4",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q4",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s4",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos4",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ia5",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ib5",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ic5",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("iz5",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p5",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q5",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s5",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos5",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ia6",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ib6",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ic6",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("iz6",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p6",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q6",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s6",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos6",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ia7",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ib7",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ic7",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("iz7",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p7",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q7",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s7",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos7",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ia8",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ib8",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ic8",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("iz8",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p8",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q8",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s8",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos8",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ia9",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ib9",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ic9",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("iz9",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p9",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q9",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s9",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos9",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ia10",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ib10",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ic10",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("iz10",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p10",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q10",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s10",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos10",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ia11",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ib11",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ic11",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("iz11",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p11",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q11",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s11",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos11",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ia12",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ib12",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ic12",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("iz12",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p12",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q12",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s12",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos12",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ia13",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ib13",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ic13",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("iz13",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p13",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q13",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s13",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos13",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ia14",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ib14",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ic14",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("iz14",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p14",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q14",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s14",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos14",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ia15",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ib15",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ic15",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("iz15",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p15",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q15",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s15",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos15",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ia16",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ib16",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ic16",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("iz16",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p16",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q16",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s16",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos16",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p1a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p1b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p1c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q1a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q1b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q1c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s1a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s1b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s1c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos1a",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos1b",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos1c",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p2a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p2b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p2c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q2a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q2b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q2c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s2a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s2b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s2c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos2a",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos2b",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos2c",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p3a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p3b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p3c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q3a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q3b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q3c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s3a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s3b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s3c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos3a",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos3b",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos3c",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p4a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p4b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p4c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q4a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q4b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q4c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s4a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s4b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s4c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos4a",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos4b",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos4c",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p5a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p5b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p5c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q5a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q5b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q5c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s5a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s5b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s5c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos5a",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos5b",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos5c",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p6a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p6b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p6c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q6a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q6b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q6c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s6a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s6b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s6c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos6a",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos6b",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos6c",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p7a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p7b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p7c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q7a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q7b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q7c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s7a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s7b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s7c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos7a",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos7b",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos7c",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p8a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p8b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p8c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q8a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q8b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q8c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s8a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s8b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s8c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos8a",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos8b",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos8c",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p9a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p9b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p9c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q9a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q9b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q9c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s9a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s9b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s9c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos9a",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos9b",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos9c",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p10a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p10b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p10c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q10a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q10b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q10c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s10a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s10b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s10c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos10a",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos10b",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos10c",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p11a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p11b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p11c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q11a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q11b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q11c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s11a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s11b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s11c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos11a",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos11b",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos11c",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p12a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p12b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p12c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q12a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q12b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q12c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s12a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s12b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s12c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos12a",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos12b",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos12c",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p13a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p13b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p13c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q13a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q13b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q13c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s13a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s13b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s13c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos13a",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos13b",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos13c",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p14a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p14b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p14c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q14a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q14b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q14c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s14a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s14b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s14c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos14a",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos14b",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos14c",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p15a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p15b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p15c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q15a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q15b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q15c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s15a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s15b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s15c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos15a",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos15b",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos15c",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p16a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p16b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("p16c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q16a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q16b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("q16c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s16a",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s16b",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("s16c",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos16a",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos16b",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("cos16c",	PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
PT_MAP_END(yc)
#if 0	/// TBD: depend on hw
	PT_ITEM("dc1",		PT_TYPE_FLOAT,
	PT_ITEM("dc2",		PT_TYPE_FLOAT,
	PT_ITEM("temperture",	PT_TYPE_FLOAT,
	PT_ITEM("huminity",	PT_TYPE_FLOAT,
#endif

/**
 * @brief Create YC desc list from DB
 * @param  dev_id	Device ID
 * @return int		0 - success
 */
int init_desc_list(int dev_id)
{
	return 0;
}

/**
 * @brief Save YC table to RT DB
 * @param entry YC table entry
 * $param name
 * @return int
 */
int yc_save_table(struct yc_table_t *base)
{
#if (defined A9APP) || (defined SIMULATOR)
	struct pt_map_array_t *entry = get_map_entry_yc();
	struct pt_map_t *map = entry->map;
	int count = entry->count;
	char key[16] = { 0 };
	char value[16] = { 0 };

	for (int i = 0; i < count; i++) {
		sprintf(key, "yc:%s:*", map->name);
		switch (map->type) {
		case PT_TYPE_FLOAT:
			sprintf(value, "%f", *(float *)((ssize_t)base + map->offset));
			break;
		default:
			sprintf(value, "0");
			break;
		}
		if (rdb_key(key, key) >= 0) {
			rdb_set_str(key, value);
		} else {
			struct yc_desc_t desc;
			char cmd[128];

			sprintf(cmd, "select * from tbl_yc_desc where alias='%s'", map->name);
			dbg("%s\n", cmd);
			if (sdb_select_single(cmd, &sdb_map_yc_desc, &desc) != 0) {
				dbg("read desc failed\n");
				return -1;
			}

			sprintf(key, "yc:%s:%d", map->name, desc.ptid);
			rdb_set_str(key, value);
		}
		map++;
	}

#else
	/// TBD: save YC from M4
#endif
	return 0;
}

/**
 * @brief
 * @param  table Desc.
 * @param  name	Desc.
 * @return int
 */
int yc_save_by_name(struct yc_table_t *table, char *name)
{
	return 0;
}

/**
 * @brief save yc by id
 * @param  table yc_table
 * @param  id	 yc internal id
 * @return int 0 - success
 */
int yc_save_by_id(void *value, int id)
{
	return 0;
}

/**
 * @brief Read YC by ID
 * @param  value Return value
 * @param  id	YC ID
 * @return int 0 - success
 */
int yc_read_single(void *value, int id)
{
	struct yc_desc_t desc;
	char cmd[128];
	char buf[RDB_REPLY_BUF_LEN] = {0};
	char key[24];

	sprintf(cmd, "select * from tbl_yc_desc where ptid=%d", id);
	dbg("%s\n", cmd);
	if (sdb_select_single(cmd, &sdb_map_yc_desc, &desc) != 0) {
		dbg("read desc failed\n");
		return -1;
	}

	sprintf(key, "yc:%s:%d", desc.alias, desc.ptid);
	if (rdb_get_str(key, buf) != TRUE) {
		return -1;
	}
	*(float *)value = atof(buf);

	return 0;
}

int yc_read_list(struct yc_value_t *list, int start, int len)
{
	return 0;
}

int yc_read_multi(void *buf, int *ids, int len)
{
	return 0;
}

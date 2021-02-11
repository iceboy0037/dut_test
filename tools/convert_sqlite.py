import xlrd
import sys
import time
import sqlite3
import os
import stat

for x in sys.argv:
	print(x)

if len(sys.argv) > 2:
	filename = sys.argv[1]
	dbname = sys.argv[2]
else:
	print("No file, exit")
	exit()

if os.path.isfile(dbname):
	print("Remove file: ", dbname)
	os.unlink(dbname)

def getTimeStr():
	fmt = "YYYY-MM-DD HH:MM:SS.SSS"
	return  time.strftime(fmt, time.localtime(time.time()))

def InitDescTable(table, cursor, devid):
	for i in range(1, table.nrows):

		# print( int(table.row_values(i)[4], 16),
		# 	table.row_values(i)[3],
		# 	table.row_values(i)[1],
		# 	table.row_values(i)[2],)
		print("insert into tbl_yc_desc (devid, ptid, fun, inf, ratio, type, name, alias)\
			values (%d, %d, %d, %d, %f, '%s', '%s', '%s')" %
			(devid,
			int(table.row_values(i)[4], 16),
			1,
			1,
			1,
			table.row_values(i)[3],
			table.row_values(i)[1],
			table.row_values(i)[2],
			))
		ret = cursor.execute("insert into tbl_yc_desc (devid, ptid, fun, inf, ratio, type, name, alias)\
				values (%d, %d, %d, %d, %f, '%s', '%s', '%s')" %
				(devid,
				int(table.row_values(i)[4], 16),
				1,
				1,
				1,
				table.row_values(i)[3],
				table.row_values(i)[1],
				table.row_values(i)[2],
				))
	return

def InitSysTable(table, cursor):
	for i in range(1, table.nrows):
		print()
	return

def InitYxTable(table, cursor, did):
	for i in range(1, table.nrows):
		print("insert into tbl_yx (devid, ptid, fun, inf, dname, alias, value, tm, count, tname, type, aname, attr)\
				values (%d, %d, %d, %d, '%s', '%s', %d, '%s', %d, '%s', '%s', '%s', '%s')" %
				(did,
				(int(table.row_values(i)[3]) << 16) + int(table.row_values(i)[4]),
				int(table.row_values(i)[3]),	# fun
				int(table.row_values(i)[4]),	# inf
				table.row_values(i)[5],			# dname
				table.row_values(i)[6],			# alias
				int(table.row_values(i)[7]),	# value
				table.row_values(i)[8],			# tm
				int(table.row_values(i)[9]),	# count
				table.row_values(i)[10],
				table.row_values(i)[11],
				table.row_values(i)[12],
				table.row_values(i)[13],
				))
		ret = cursor.execute("insert into tbl_yx (devid, ptid, fun, inf, dname, alias, value, tm, count, tname, type, aname, attr)\
				values (%d, %d, %d, %d, '%s', '%s', %d, '%s', %d, '%s', '%s', '%s', '%s')" %
				(did,
				(int(table.row_values(i)[3]) << 16) + int(table.row_values(i)[4]),
				int(table.row_values(i)[3]),	# fun
				int(table.row_values(i)[4]),	# inf
				table.row_values(i)[5],		# dname
				table.row_values(i)[6],		# alias
				int(table.row_values(i)[7]),	# value
				table.row_values(i)[8],		# tm
				int(table.row_values(i)[9]),	# count
				table.row_values(i)[10],
				table.row_values(i)[11],
				table.row_values(i)[12],
				table.row_values(i)[13],
				))
	return

devid = 0xff
tables = [
	# System parameters
	{
		"sheet": "",
		"name" : "tbl_sys",
		"cmd" : "create table tbl_sys \
			(	devid	integer not null,\
				ptid 	integer primary key not null,\
				fun	integer not null,\
				inf 	integer not null,\
				dname	text not null,\
				alias	text not null,\
				value	text not null,\
				dtype	text not null,\
				tm	text not null,\
				rw	int not null,\
				unit	text not null,\
			);"
	},

	# Run parameters
	{
		"sheet": "",
		"name" : "tbl_run",
		"cmd" : "create table tbl_run \
			(	id 	integer primary key autoincrement not null,\
				ptid	integer not null,\
				type	text not null,\
				value	text not null,\
				def 	text not null,\
				max	text not null,\
				min	text not null,\
				step	text not null,\
				alias	text not null,\
				name	text not null,\
				desc	text not null,\
				rw	integer not null,\
				notify	text not null,\
				modify	text not null\
			);"
	},

	# YC description table
	{
		"sheet": "",
		"name" : "tbl_yc_desc",
		"cmd" : "create table tbl_yc_desc \
			(	devid	integer not null,\
				ptid 	integer primary key not null,\
				fun	integer not null,\
				inf 	integer not null,\
				ratio	real not null,\
				type	text not null,\
				name	text not null,\
				alias	text not null\
			);"
	},

	# Protocol transfer table
	{
		"sheet": "",
		"name": "tbl_trans",
		"cmd" : "create table tbl_trans \
			(	id 	integer primary key autoincrement not null,\
				devid	integer not null,\
				proid	integer not null,\
				ptid 	integer not null,\
				type	text not null\
			);"
	},

	# YC value tables
	{
		"sheet": "",
		"name" : "tbl_yc_value",
		"cmd" : "create table if not exists tbl_yc_value \
			(\
				ptid	integer primary key not null,\
				value	real not null\
			);"
	},

	# YX table
	{
		"sheet": "",
		"name" : "tbl_yx",
		"cmd" : "create table if not exists tbl_yx \
			(\
				devid	integer not null,\
				ptid	integer primary key not null,\
				fun	integer not null,\
				inf	integer not null,\
				dname	text not null,\
				alias	text not null,\
				value	integer not null,\
				tm	text not null,\
				count	integer not null,\
				tname	text not null,\
				type	text not null,\
				aname	text not null,\
				attr	text not null\
			);"
	},
]

# 1. Create DB connection
conn = sqlite3.connect(dbname)

# 2. Create Cursor
cursor = conn.cursor()

# 3. Create tables
print("Create tables\n")
for x in tables:
	print("Create table: %s" % x["name"])
	cursor.execute(x["cmd"])


# 4. Read data from xls
data = xlrd.open_workbook(filename)
for x in data.sheets():
	print(x.name)

table = data.sheets()
InitDescTable(table[2], cursor, devid)
InitYxTable(table[4], cursor, devid)

cursor.close()
conn.commit()
conn.close()
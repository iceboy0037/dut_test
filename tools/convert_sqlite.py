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
	return  time.strftime("%Y-%m-%d %H:%M:%S" ,time.localtime(time.time()))

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
		print(ret)
	return

def InitSysTable(table, cursor):
	for i in range(1, table.nrows):
		print()
	return

devid = 0xff
tables = [
	# System parameters
	{
		"name" : "tbl_sys",
		"cmd" : "create table tbl_sys \
			(	id 	integer primary key autoincrement not null,\
				desc 	text not null,\
				name 	text not null,\
				ptid 	integer not null,\
				type 	text not null\
			);"
	},

	# Run parameters
	{
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
		"name" : "tbl_yc_value",
		"cmd" : "create table if not exists tbl_yc_value \
			(\
				ptid	integer primary key not null,\
				value	real not null\
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

cursor.close()
conn.commit()
conn.close()
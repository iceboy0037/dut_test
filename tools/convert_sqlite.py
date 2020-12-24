import xlrd
import sys
import time
import sqlite3
import os

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
	return  time.strftime("%Y-%m-%d %H:%M:%S" ,time.localtime(time.time()))

def InitDescTable(table, cursor, devid):
	for i in range(1, table.nrows):

		print( int(table.row_values(i)[4], 16),
			table.row_values(i)[3],
			table.row_values(i)[1],
			table.row_values(i)[2],)
		print("insert into tbl_yc_desc (\
			devid, ptid, fun, inf, ratio, type, name, alias)\
			values (%d, %d, %d, %d, %f, %s, %s, %s)" %
			(devid,
			int(table.row_values(i)[4], 16),
			1,
			1,
			1,
			table.row_values(i)[3],
			table.row_values(i)[1],
			table.row_values(i)[2],
			))

		cursor.execute("insert into tbl_yc_desc (\
			devid, ptid, fun, inf, ratio, type, name, alias)\
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

tables = {
	# System parameters

	"create table tbl_sys \
	(	id 	integer primary key autoincrement not null,\
		desc 	text not null,\
		name 	text not null,\
		ptid 	integer not null,\
		type 	text not null\
	);",

	# Run parameters
	"create table tbl_run \
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
	);",

	# YC description table
	"create table tbl_yc_desc \
	(	id 	integer primary key autoincrement not null,\
		devid	integer not null,\
		ptid 	integer not null,\
		fun	integer not null,\
		inf 	integer not null,\
		ratio	real not null,\
		type	text not null,\
		name	text not null,\
		alias	text not null\
	);",

	# YC value tables
	"create table tbl_yc_value \
	(	id	integer primary key autoincrement not null,\
		ptid	integer not null,\
		rating	real not null,\
		raw	real not null,\
		result	real not null,\
		q	integer not null\
	);"
}

cursor = sqlite3.connect(dbname).cursor()
print("Create tables\n")
for x in tables:
	cursor.execute(x)

# open database xls
data = xlrd.open_workbook(filename)
for x in data.sheets():
	print(x.name)

table = data.sheets()
InitDescTable(table[2], cursor, 0xff)

sqlite3.connect(dbname).commit()
sqlite3.connect(dbname).close()

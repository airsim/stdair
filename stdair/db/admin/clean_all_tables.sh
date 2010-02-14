#!/bin/sh
#
# Two parameters are optional:
# - the host server of the database
# - the port of the database
#

if [ "$1" = "-h" -o "$1" = "--help" ];
then
	echo "Usage: $0 [<Database Server Hostname> [<Database Server Port>]]"
	echo ""
	exit -1
fi

##
# Database Server Hostname
DB_HOST="localhost"
if [ "$1" != "" ];
then
	DB_HOST="$1"
fi

# Database Server Port
DB_PORT="3306"
if [ "$2" != "" ];
then
	DB_PORT="$2"
fi

# Database User
DB_USER="dsim"

# Database Password
DB_PASSWD="${DB_USER}"

# Database Name
DB_NAME="dsim"

# Count the number of elements of a given database table
function countElements() {
	echo
	echo "Number of elements for the '${DB_TABLE}' table"
	SQL_QUERY="select count(*) from ${DB_TABLE}"
	mysql -u ${DB_USER} --password=${DB_PASSWD} -P ${DB_PORT} -h ${DB_HOST} -e "${SQL_QUERY}" ${DB_NAME}
}

# Delete all the elements of a given database table
function deleteAllElements() {
	SQL_QUERY="delete from ${DB_TABLE}"
	mysql -u ${DB_USER} --password=${DB_PASSWD} -P ${DB_PORT} -h ${DB_HOST} -e "${SQL_QUERY}" ${DB_NAME}
}

#
TABLES="airlines"

# Count rows
echo "Before:"
for table_name in ${TABLES}
do
	DB_TABLE="${table_name}"
	countElements
done

# Delete tables
echo "Deletion..."
for table_name in ${TABLES}
do
	DB_TABLE="${table_name}"
	deleteAllElements
done
echo "Done"

## After deleting elements (sanity check)
echo
echo "After:"
for table_name in ${TABLES}
do
	DB_TABLE="${table_name}"
	countElements
done
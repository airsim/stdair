#!/bin/sh
#
# Two parameters are optional:
# - the host server of the database
# - the port of the database
#

if [ "$1" = "-h" -o "$1" = "--help" ];
then
	echo "Usage: $0 [<DB User> [<DB Name> [<DB Hostname> [<DB Port>]]]]"
	echo ""
	exit -1
fi

##
# Database Username/account name
DB_USER="dsim"
if [ "$1" != "" ];
then
    DB_USER="$1"
fi

# Database Password
DB_PASSWD="${DB_USER}"

# Database Name
DB_NAME="sim_dsim"
if [ "$2" != "" ];
then
    DB_NAME="$2"
fi

# Database Server Hostname
DB_HOST="localhost"
if [ "$3" != "" ];
then
    DB_HOST="$3"
fi

# Database Server Port
DB_PORT="3306"
if [ "$4" != "" ];
then
    DB_PORT="$4"
fi


# Count the number of elements of a given database table
function countElements() {
    echo
    echo "  Number of elements for the '${DB_USER}'@'${DB_NAME}'.'${DB_TABLE}' table"
    SQL_QUERY="select count(*) from ${DB_TABLE}"
    mysql -u ${DB_USER} --password=${DB_PASSWD} -P ${DB_PORT} -h ${DB_HOST} -e "${SQL_QUERY}" ${DB_NAME}
    echo
}

# Delete all the elements of a given database table
function deleteAllElements() {
    echo "  Deleting all the rows from the '${DB_USER}'@'${DB_NAME}'.'${DB_TABLE}' table..."
    SQL_QUERY="delete from ${DB_TABLE}"
    mysql -u ${DB_USER} --password=${DB_PASSWD} -P ${DB_PORT} -h ${DB_HOST} -e "${SQL_QUERY}" ${DB_NAME}
    echo "  ... Done: all the rows have been deleted from the '${DB_USER}'@'${DB_NAME}'.'${DB_TABLE}' table."
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
echo "Deletion for the following tables: '${TABLES}'"
for table_name in ${TABLES}
do
    DB_TABLE="${table_name}"
    deleteAllElements
done
echo "... Done: all the tables (i.e., '${TABLES}') have been emptied."

## After deleting elements (sanity check)
echo
echo "After:"
for table_name in ${TABLES}
do
    DB_TABLE="${table_name}"
    countElements
done

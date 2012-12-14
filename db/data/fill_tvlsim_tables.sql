--
-- Load the simulator configuration details into the MySQL table
--
load data local infile 'airlines.csv' ignore 
into table airlines
fields terminated by ',' enclosed by '' escaped by '\\' 
ignore 1 lines;

--
-- Create the 'airinv' user, with standard (non-administrator) privileges
--

-- With the GRANT statement, when the user is not already existing
-- it is created.
GRANT SELECT, INSERT, UPDATE, DELETE, CREATE, DROP, FILE, INDEX, ALTER,
      CREATE TEMPORARY TABLES, CREATE VIEW, EVENT, TRIGGER, SHOW VIEW, 
      CREATE ROUTINE, ALTER ROUTINE, EXECUTE ON *.* 
      TO 'airinv'@'localhost' IDENTIFIED BY 'airinv';
GRANT SELECT, INSERT, UPDATE, DELETE, CREATE, DROP, FILE, INDEX, ALTER,
      CREATE TEMPORARY TABLES, CREATE VIEW, EVENT, TRIGGER, SHOW VIEW, 
      CREATE ROUTINE, ALTER ROUTINE, EXECUTE ON *.* 
      TO 'airinv'@'%' IDENTIFIED BY 'airinv';

-- Tell MySQL that a new user has arrived in town
flush privileges;


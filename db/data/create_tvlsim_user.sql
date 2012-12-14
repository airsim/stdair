--
-- Create the 'tvlsim' user, with standard (non-administrator) privileges
--

-- With the GRANT statement, when the user is not already existing
-- it is created.
GRANT SELECT, INSERT, UPDATE, DELETE, CREATE, DROP, FILE, INDEX, ALTER,
      CREATE TEMPORARY TABLES, CREATE VIEW, EVENT, TRIGGER, SHOW VIEW, 
      CREATE ROUTINE, ALTER ROUTINE, EXECUTE ON *.* 
      TO 'tvlsim'@'localhost' IDENTIFIED BY 'tvlsim';
GRANT SELECT, INSERT, UPDATE, DELETE, CREATE, DROP, FILE, INDEX, ALTER,
      CREATE TEMPORARY TABLES, CREATE VIEW, EVENT, TRIGGER, SHOW VIEW, 
      CREATE ROUTINE, ALTER ROUTINE, EXECUTE ON *.* 
      TO 'tvlsim'@'%' IDENTIFIED BY 'tvlsim';

-- Tell MySQL that a new user has arrived in town
flush privileges;

CREATE OR REPLACE
TYPE CONTRec AS OBJECT 
( 
CNTY_CODE                CHAR(3),
 NUM_CODE                CHAR(3),
 TWO_CODE                CHAR(2), 
 SHORT_NAME              VARCHAR2(20 CHAR),
 FULL_NAME               VARCHAR2(40 CHAR)
);

CREATE OR REPLACE TYPE CONTTABLE IS TABLE OF CONTRec;

CREATE OR REPLACE PACKAGE SqlJavaTestpro AS
PROCEDURE testCallProcedureFromJava(table_data OUT CONTTABLE);
END SqlJavaTestpro;

/
CREATE OR REPLACE PACKAGE BODY SqlJavaTestpro AS

PROCEDURE testCallProcedureFromJava(table_data OUT CONTTABLE) IS

BEGIN

SELECT contrec(cnty_code,num_code,two_code,short_name,full_name) BULK COLLECT INTO table_data
FROM COUNTRY;

END testCallProcedureFromJava;
END SqlJavaTestpro;

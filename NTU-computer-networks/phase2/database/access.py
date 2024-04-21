import sqlite3

conn = sqlite3.connect("./database/data.db", check_same_thread=False)
c = conn.cursor()
c.execute( 
    "CREATE TABLE IF NOT EXISTS USERTABLE \
    (\
    AGENT          CHAR(50)    NOT NULL, \
    USERNAME       CHAR(50)    NOT NULL, \
    PASSWORD       CHAR(50)    NOT NULL, \
    ONLINE         BOOLEAN     NOT NULL  \
    );"
)

c.execute( 
    "CREATE TABLE IF NOT EXISTS COMMENTTABLE \
    (\
    USERNAME       CHAR(50)    NOT NULL, \
    MESSAGE        TEXT        NOT NULL  \
    );"
)

def login(agent, username, password):
   cursor = c.execute(f"select * from usertable where username='{username}' and password='{password}';")
   if len(list(cursor))==0: return False
   c.execute(f"update usertable set online='true',agent='{agent}' where username='{username}';")
   conn.commit()
   return True

def login_status(agent):
   cursor = c.execute(f"select * from usertable where agent='{agent}' and online='true';")
   if len(list(cursor))==0: return "false"
   return list(cursor)[0][1]

def logout(agent):
   c.execute(f"update usertable set online='false' where agent='{agent}';")
   conn.commit()

def register(username, password):
   c.execute( 
      f" INSERT INTO USERTABLE (AGENT,USERNAME,PASSWORD,ONLINE) \
         VALUES (('null'),'{username}', '{password}','false')"
   )
   conn.commit()

def comment(username,msg):
   c.execute( 
      f" INSERT INTO COMMENTTABLE (USERNAME,MESSAGE) \
         VALUES ('{username}', '{msg}')"
   )
   conn.commit()

def get_comment_data():
   cursor = c.execute("select * from commenttable;")
   return list(cursor)

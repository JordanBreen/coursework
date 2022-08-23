import pandas as pd
import sqlite3

xlsxFilePath  = 'C:/Users/jorda/Desktop/feat.xlsx'
dbFilePath    = 'C:/Users/jorda/Desktop/Pathfinder.db'
dbFileName    = 'feat'
actionOnExist = 'append'

xlsxFileData = pd.read_excel(xlsxFilePath,
                             sheet_name=0,
                             header=0)

"""Connect to existing database at path, creates new if one doesn't already exist"""
db_conn = sqlite3.connect(dbFilePath)
"""Create cursor to interact with target database"""
c = db_conn.cursor()

xlsxFileData.to_sql(dbFileName, 
                    db_conn, 
                    if_exists = actionOnExist, 
                    index=False)
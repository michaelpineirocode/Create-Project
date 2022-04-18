# Author: Steven Pineiro
# License: MIT
#
import pandas as pd
df = pd.read_csv('Data/population2020.csv')
df.drop(df.columns.difference(['Country (or dependency)', 'Population (2020)']), 1, inplace=True)
print(df)
df.to_csv('Data/population.csv', index=False)

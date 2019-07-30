#!/usr/bin/python

import numpy as np 
import pandas as pd 
# Input data files are available in the "../input/" directory.
# For example, running this (by clicking run or pressing Shift+Enter) will list the files in the input directory
import matplotlib.pyplot as plt
import seaborn as sns



fbdata= pd.read_csv("pseudo_facebook.csv")
fbdata.head()


#Exploring data
fbdata.describe()

*********************************
********DO FILE EXAMPLE**********
*********************************



**输入存储路径
**define the storage path
cd ""

**清除内存中的数据
**clear data in the memory
clear

**打开log文件
**open log file
log using "test.log", replace

**打开数据文件
**open data file
use EduIncome.dta

**数据的处理
**Data processing

*描述性统计
*descriptive statistics

tab gender  //男性和女性的比例 show the percentage of men and women
summ birthyear empjob_twage //对年龄和工资进行描述性统计 descriptive statistics for age and wage
bysort gender : summ birthyear empjob_twage  //按照性别对年龄和工资进行描述性统计 descriptive statistics for age and wage by gender

*生成一些新变量
*generate some new variables
gen age = 2020 - birthyear
gen lnwage = ln(empjob_twage)  //生成natural log值 generate natural logarithmic variable
egen meanage = mean(age)  //生成新变量等于年龄的均值 generate a new variable equal to mean value of age 
gen female = (gender == 2)
gen edu = schooling_yr

*计算回归式系数
*estiamte the regression equation: reg y x1 x2
reg lnwage age schooling_yr

*计算拟合值和残差
* estimate the fitted value and the residuals (run after "reg")
* Fitted value: predict xx, where xx is the variable name of the fitted value
* Residuals: predict xx, residuals, where xx is the variable name of the residuals
predict yhat
predict ehat, residuals

**关闭log文件
**close the log file
log close


* Other commands might be useful:
*管理变量的顺序
*change the order of variables 
order lnwage age gender marriage edu

*对数据排序
*sort data
sort edu  

*更换变量名
*change variable name
rename schooling_yr edu

*更换某些变量的观测值
*change observations of some variables
replace edu = . if edu == 0 // . represents missing value, they are not used in regressions.

*去掉或保留某些观测值
*drop or save some observations
keep if edu != .
drop if edu == .

*去掉或保留某些变量
*drop or save some variables
keep lnwage edu age gender marriage birthyear
drop birthyear

*将处理好的数据保存为新的数据文件
*save the processed data as a new data file
save "mydata.dta", replace

**画图
**plotting

*直方图
*histogram
histogram lnwage //画工资分布的直方图 plot histogram of the distribution of the wage variable

*散点图
*scatter plot
twoway scatter lnwage age //画工资与年龄的散点图 plot the scatter plot of wage versus age

*X与Y的拟合线
*fitted line of X and Y
twoway lfitci lnwage age  //工资与年龄的拟合线 plot the fitted line of wage and age

**help file
help regress
help predict

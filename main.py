import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


def per_day(x):
    p = []
    p.append(x[0])
    prvs = x[0]
    for i in range(1, len(x)):
        p.append(x[i] - prvs)
        prvs = x[i]
    return p


def summary_plot(data, yandex_sick, yandex_deaths):
    a = data.values[0]
    b = data.values[1]
    c = data.values[2]
    e = data.values[3]
    ys = yandex_sick[:len(a)]
    ys_ff = yandex_sick[2:len(a) + 2]
    yd = yandex_deaths[:len(a)]
    plt.plot(a, e, label='смоделированное число умерших за все время')
    plt.plot(a, yd, label='данные статистики')
    plt.xlabel('дни')
    plt.ylabel('число умерших')
    plt.legend()
    plt.show()
    plt.plot(a, b, label='смоделированное число заболевших за все время')
    plt.plot(a, [s*1.09 for s in ys], label='выявленное число заболевших за все время')
    plt.plot(a, ys, label='данные статистики')
    plt.xlabel('дни')
    plt.ylabel('число заболевших')
    plt.legend()
    plt.show()


def plot_per_day(data, yandex_sick, yandex_deaths):
    a = data.values[0]
    b = data.values[1]
    c = data.values[2]
    e = data.values[3]
    f = data.values[5]
    ys = yandex_sick[:len(a)]
    yd = yandex_deaths[:len(a)]
    c_pd = per_day(c)
    b_pd = per_day(b)
    e_pd = per_day(e)
    f_pd = per_day(f)
    ys_pd = per_day(ys)
    yd_pd = per_day(yd)
    # deaths_pd = per_day(deaths)
    plt.plot(a, e_pd, label='смоделированное число умерших за сутки')
    plt.plot(a, yd_pd, label='данные статистики')
    plt.xlabel('дни')
    plt.ylabel('число умерших')
    plt.legend()
    plt.show()
    plt.plot(a, b_pd, label='смоделированное число заразившихся за сутки')
    plt.plot(a, ys_pd, label='данные статистики')
    plt.plot(a, f_pd, label='Выявленное число заболевших в модели')
    plt.xlabel('дни')
    plt.ylabel('число заболевших')
    plt.legend()
    plt.show()


# скорее всего, 3 разных csv для того, чтобы получить усредненные данные
data = pd.read_csv('C:\\Users\\bfghb\\source\\repos\\AgentModel\\AgentModel\\data.csv')
data2 = pd.read_csv('C:\\Users\\bfghb\\source\\repos\\AgentModel\\AgentModel\\data2.csv')
data3 = pd.read_csv('C:\\Users\\bfghb\\source\\repos\\AgentModel\\AgentModel\\data3.csv')
yandex_sick = pd.read_csv('yandex_sick.csv', header=None)
yandex_deaths = pd.read_csv('yandex_deaths.csv', header=None)
yandex_sick = yandex_sick.values[0]
yandex_deaths = yandex_deaths.values[0]

d1 = data.values[1]
d2 = data2.values[1]
d3 = data3.values[1]
# d = d1 + d2 + d3
# d = d / 3
d = d1

a = data.values[0]
b = data.values[1]
c = data.values[2]
e = data.values[3]
days = [i for i in range(111)]
# days = [i for i in range(91)]
# deaths = pd.Series([0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 3, 4, 6, 11, 16, 19, 20, 27, 29, 29, 31, 31, 38, 50, 58, 72, 82, 95, 106, 113, 127,148, 176, 204, 233, 261, 288, 325, 366, 404, 435, 479, 546, 611, 658, 695, 729, 764, 816, 866, 905, 956, 1010, 1068, 1124, 1179, 1232, 1290, 1358, 1432,1503, 1580, 1651, 1726, 1794, 1867, 1934, 1993, 2034, 2110, 2183, 2254, 2330, 2408, 2477, 2553, 2624, 2685, 2749, 2806, 2864, 2919, 2970, 3029, 3085, 3138, 3187, 3231, 3281, 3334])
# plt.plot(a, b)
# plt.plot(a, c)

# plt.plot(a, e, label='смоделированное число умерших')
# plt.plot(a, deaths, label='данные статистики')
# plt.xlabel('дни')
# plt.ylabel('число умерших')
# plt.legend()
# plt.show()
summary_plot(data, yandex_sick, yandex_deaths)
plot_per_day(data, yandex_sick, yandex_deaths)
# print(deaths.tolist())
# print(per_day(deaths.tolist()))

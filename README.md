# Агентные модели эпидемий применительно к вспышке Covid-19
Основа программы - класс Agent, в котором есть поля age, dayOfIllness, infected, death,
self_isolation, test, stage, asymptomatic. С точки зрения построения математической
модели рассматривается множество агентов {ai}, где каждому агенту сопоставлен
набор параметров и бинарных статусов. Параметр Age задает возраст агента, он
необходим при расчете вероятности летального исхода, так как известно, что чем
больше возраст, тем выше риски(Рис. 1). Я использую возрастной состав РФ.
Все агенты разделены на три категории: здоровые люди, которые не переболели
вирусом (H), агенты в стадии болезни, вызванной вирусом SARS-CoV-2 (I) и
переболевшие коронавирусом (R).
Изменяемая характеристика 𝑡 определяет сколько дней человек заражен Covid-19. У 𝑖
здоровых людей (ai ∈ H) значение ti = -1, в день заражения данный параметр
увеличивается на 1 и становится равен 0, и так далее, до выздоровления после 20 дня,
либо летального исхода. Бинарные статусы I, D, SI, T определяют заражение,
летальных исход, нахождение на самоизоляции и проходил ли он тестирование. Поле
stage хранит в себе стадию заболевания агента. Как мы знаем, при заражении вирусом
Covid-19 выделяется несколько основных стадий(Рис. 2):
- агент, восприимчивый к вирусу (‘n’) - стадия, в которой находятся агенты, не
болевшие Covid-19
- отсутствие симптомов (‘w’) - данная стадия длится в среднем три дня, у агента
нет признаков заболевания, однако он уже представляет опасность для других
людей.
- появление признаков заболевания (‘s’) - данная стадия длится 7 дней. Человек
замечает симптомы заболевания, с определенной вероятностью останется дома
и сделает тест на коронавирус.
- вероятность летального исхода (‘t’) - длительность 10 дней. В этот период у
агента есть шанс смертельного исхода [4] Этот шанс зависит от возраста
человека и, так как стадия длится 10 дней, он используется с коэффициентом 1
10
- выздоровление (‘r’) - стадия, на которой болезнь заканчивается. У человека
появляется иммунитет к Covid-19. На коротком промежутке времени мы можем
считать, что вероятность заразится повторна крайне мала.

![image](https://user-images.githubusercontent.com/45105942/181919812-ae120b8d-573f-4bba-911b-c7b92b0924d7.png)
Рис. 1. Зависимость вероятности летального исхода от возраста

![image](https://user-images.githubusercontent.com/45105942/181919841-b4ecc2d2-2fbd-4235-bcb3-bbfb8f3cefb2.png)
Рис. 2. Стадии сценария болезни, используемые в модели. Этап n - (𝑡_𝑖 = -1), 
w - (0≤ 𝑡_𝑖 ≤ 3), s - (4 ≤ 𝑡_𝑖 ≤ 10), t - (11 ≤ 𝑡_𝑖 ≤ 20), r - (𝑡_𝑖 = -1)

Конечно, не все люди болеют одинаково и длительность разных стадий может
меняться, однако, с большим количеством агентов мы можем усреднить эти значения,
что не повлечет серьезных изменений в результатах, однако заметно снизит сложность
модели.
Также, в программе есть несколько констант, которые непосредственно влияют на
эксперимент. Например, количество агентов, длительность эксперимента, количество
социальных контактов, коэффициент заразности вируса и тд.

![image](https://user-images.githubusercontent.com/45105942/181919859-95cced95-0052-4d3f-b25a-ba30c279c629.png)
Рис.3. Определение множества агентов, которых может заразить инфицированный агент.

Ключевой особенностью работы является взаимодействие агентов между собой.
Существует подход, при котором агент просто взаимодействует с n случайными
людьми и заражает каждого с определенной вероятностью [7]. Однако, если
задуматься, больше всего времени человек проводит с людьми, которых хорошо
знает(родственники, друзья, коллеги) и вероятность заразиться у них гораздо выше,
чем у случайного человека в супермаркете, с которым агент фактически не
контактировал, так как для вирусных заболеваний важна инфицирующая доза, а не
факт контакта. Поэтому, я решил, что следует сделать вероятным передачу вируса
только для n ближайших агентов(это значение определяется числом социальных
контактов (Рис. 3)).
Агент an может заразить только агентов из множества
{ aj | j ∈[n -𝑛/2 ,n + 𝑛/2},
где 𝑛 - число социальных контактов (number of social contacts)(Рис. 3)
ξ - случайная величина, равномерно распределенная в интервале [0,1]
p - вероятность передачи вируса от одного агента к другому, [0, 1]
Если генератор псевдослучайных чисел на [0, 1] выдает значение ξ < p зараженный
агент передает вирус здоровому.
Немаловажным параметром для работы программы является число заболевших на
начало эксперимента. По официальной статистике на 15 марта в Москве было 50
зараженных, поэтому я использую такое значение. Задав число заболевших на начало
эксперимента программа случайным образом выбирает этих людей из числа всех
агентов. Работа программы происходит в цикле по дням. Каждый день заболевшие
агенты контактируют с остальными и с определенной вероятностью могут их заразить.
При появлении первых симптомов человек с заданной вероятностью остается дома и
делает тест. При положительном результате тестирование проходят 4 человека из
ближайшего круга общения.

![image](https://user-images.githubusercontent.com/45105942/181923541-a0eac874-ff6d-4871-878d-4125063a7781.png)
Рис. 4. Схема агентной модели.

На Рис. 4 изображены переходы агентов между различными множествами в модели.
Как видим, человек может переболеть как с симптомами, так и без. При этом,
вероятность летального исхода есть только у больных вирусов с проявлением
симптомов.
Существуют разные данные о проценте бессимптомных заболевших Covid-19[8, 9, 10].
Я усреднил данные нескольких исследований и выбрал значение в 25% бессимптомных
заболевших.
При появлении первых симптомов человек делает тест с вероятностью t (0.7)
Точность тестирования составляет a (0.92)
ξ - случайная величина, равномерно распределенная в интервале [0,1]
t - вероятность с которой агент с симптомами Covid-19 сдаст тест
a - точность тестирования
В реальности, тестов делалось гораздо больше, многим людям приходилось регулярно
тестироваться на работе. Чтобы соблюсти объемы тестирования в своей модели я
добавил реальную статистику количества протестированных(Рис. 5). К сожалению, мне
удалось найти эти данные только для всей России, поэтому я использовал их для
Москвы с коэффициентом . После того, как протестировались агенты с симптомами, 1/9
количество оставшихся тестов случайным образом распределяется среди всей
популяции. Таким образом, есть шанс выявить вирус на ранней стадии, либо у агента,
переносящего Covid-19 бессимптомно.

![image](https://user-images.githubusercontent.com/45105942/181923627-e2080194-8f94-49a1-b8f6-0592f8b137c1.png)
Рис. 5. Количество проведенных тестов по России с 23 марта 2020 года.

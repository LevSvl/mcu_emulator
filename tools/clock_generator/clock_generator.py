import matplotlib.pyplot as plt

MHz = 1000000
SAMPLE_RATE = 500  # Частота дискретизации в наносекундах

""" Сигнал 1 """
# Частотные характеристики сигнала
CLK1_FREQUENCY = 10*MHz
CLK1_PERIOD_NS = int(1/CLK1_FREQUENCY * 1000000000)
CLK1_RISE_TIME_NS = CLK1_FAIL_TIME_NS = 10
CLK1_DUTY_CYCLE = 30
# Задержка перед генерацией сигнала
CLK1_DELAY_TIME_NS = 60
# Начальное значение
CLK1_LVL_INITIAL = 0

""" Сигнал 2 """
# Частотные характеристики сигнала
CLK2_FREQUENCY = 8*MHz
CLK2_PERIOD_NS = int(1/CLK2_FREQUENCY * 1000000000)
CLK2_RISE_TIME_NS = CLK2_FAIL_TIME_NS = 10
CLK2_DUTY_CYCLE = 30
# Задержка перед генерацией сигнала
CLK2_DELAY_TIME_NS = 60
# Начальное значение
CLK2_LVL_INITIAL = 0


def clk_generate(period, duty_cycle, t_rise, t_fail, t_delay, lvl_initial):
    t_high = int((period / 100) * duty_cycle)
    t_low = int(period - t_high - t_rise - t_fail)
    num_of_periods = int(SAMPLE_RATE / period)

    clk_values = list()
    time_values = list()

    time_current = t_delay
    clk_values = [lvl_initial for _ in range(t_delay)]

    for Ti in range(num_of_periods):
        """ Raising edge """
        clk_values.extend([0 for _ in range(t_rise)])
        time_values.extend(i for i in range(time_current if Ti > 0 else 0, time_current + t_rise))
        time_current += t_rise
        """ High level + Failing edge """
        clk_values.extend([1 for _ in range(t_high + t_fail)])
        time_values.extend(i for i in range(time_current, time_current + t_high + t_fail))
        time_current += (t_high + t_fail)
        """ Low level """
        clk_values.extend([0 for _ in range(t_low)])
        time_values.extend(i for i in range(time_current, time_current + t_low))
        time_current += t_low

    # Убрать лишнее
    while len(time_values) > SAMPLE_RATE:
        time_values.pop()
    while len(clk_values) > SAMPLE_RATE:
        clk_values.pop()
    
    return time_values, clk_values



if __name__ == "__main__":
    clk1_t, clk1_v = clk_generate(CLK1_PERIOD_NS, CLK1_DUTY_CYCLE, CLK1_RISE_TIME_NS, 
                                  CLK1_FAIL_TIME_NS, CLK1_DELAY_TIME_NS, CLK1_LVL_INITIAL)
    clk2_t, clk2_v = clk_generate(CLK2_PERIOD_NS, CLK2_DUTY_CYCLE, CLK2_RISE_TIME_NS, 
                                  CLK2_FAIL_TIME_NS, CLK2_DELAY_TIME_NS, CLK2_LVL_INITIAL)
    fig, axs = plt.subplots(2, figsize=(10, 4))
    fig.suptitle('Тактовые сигналы на вход i8080')
    axs[0].set_title('φ1')
    axs[0].set_xlabel("Время (нс)")
    axs[0].set_ylabel("Значение")
    axs[0].plot(clk1_t, clk1_v)
    axs[1].set_title('φ2')
    axs[1].set_xlabel("Время (нс)")
    axs[1].set_ylabel("Значение")
    axs[1].plot(clk2_t, clk2_v)
    plt.tight_layout()
    plt.show()
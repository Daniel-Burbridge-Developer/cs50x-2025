import time


def get_current_time():
    curtime = time.localtime()
    formatted_time = f"{curtime.tm_year} - {curtime.tm_mon} - {curtime.tm_yday} - {curtime.tm_hour}:{curtime.tm_min}"

    return formatted_time

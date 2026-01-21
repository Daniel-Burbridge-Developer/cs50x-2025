import schedule
from utils import get_current_time
from image import generate_image


def start_scheduler():
    schedule.every().day.at("06:00").do(wake_up)


def wake_up():
    print(f"{get_current_time()}: System Online")
    generate_image()

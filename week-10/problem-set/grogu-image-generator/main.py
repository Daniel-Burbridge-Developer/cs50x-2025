import random
import os
from io import BytesIO
import requests
from dotenv import load_dotenv
from google import genai
from google.genai import types
from image import do_the_image_stuff
from scheduling import start_scheduler

import schedule
import time

from discord import send_to_discord

load_dotenv()
# Adjusts predictability of LLM
CREATIVE_CONFIG = types.GenerateContentConfig(temperature=1.5)


DISCORD_WEBHOOK_URL = os.environ["DISCORD_WEBHOOK_URL"]
HF_TOKEN = os.environ.get("HF_TOKEN")
OUTPUT_DIR = "./output"


def run_program():
    print("starting up!")
    start_scheduler()
    schedule.every(1).minute.do(report_idle)
    schedule.every(1).hour.do(report_wake_up)
    schedule.every().day.at("06:00").do(report_wake_up)

    while True:
        schedule.run_pending()
        time.sleep(1)


def main():
    run_program()


def get_current_time():
    curtime = time.localtime()
    formatted_time = f"{curtime.tm_year} - {curtime.tm_mon} - {curtime.tm_yday} - {curtime.tm_hour}:{curtime.tm_min}"

    return formatted_time


def report_idle():
    print("Resting " + get_current_time())


def report_wake_up():
    print("Getting a Grogu! " + get_current_time())
    do_the_image_stuff()


if __name__ == "__main__":
    main()

import os
import random
import time
import requests
from dotenv import load_dotenv
from google import genai


def main():
    load_dotenv()
    prompt, file_name = generate_prompt()
    generate_image(prompt, file_name)


def generate_image(
    prompt="Cinematic shot of Baby Yoda (Grogu) wearing a knitted scarf, holding a cup of hot cocoa, autumn forest background, hyper-realistic, 8k, soft lighting, depth of field",
    file_name="todays_image",
):
    seed = random.randint(1, 1000000)
    url = f"https://image.pollinations.ai/prompt/{prompt}?width=1024&height=1024&seed={seed}&model=flux"

    print(f"Requesting Grogu from Pollinations (Seed: {seed})...")

    try:
        response = requests.get(url, timeout=30)

        if response.status_code == 200:
            # Save it to the current folders
            with open(file_name, "wb") as f:
                f.write(response.content)
            print(f"Success! Saved to {file_name}")
            return file_name
        else:
            print(f"Failed. Status Code: {response.status_code}")
            return None

    except Exception as e:
        print(f"Error: {e}")
        return None


def generate_prompt():
    client = genai.Client()

    response = client.models.generate_content(
        model="gemini-3-flash-preview",
        contents="Generate a prompt to create a unique grogu image based on the most notable headline from today.",
    )

    image_generate_prompt = response.text
    print(f"Image Prompt: {image_generate_prompt}")

    response = client.models.generate_content(
        model="gemini-3-flash-preview",
        contents=(
            f"Please create a short file name based on the image this will create: {image_generate_prompt}"
        ),
    )

    file_name = response.text
    print(f"FIle Name: {file_name}")

    return image_generate_prompt, file_name


if __name__ == "__main__":
    main()

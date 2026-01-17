import os

from dotenv import load_dotenv
from huggingface_hub import InferenceClient

load_dotenv()

client = InferenceClient(
    provider="hf-inference",
    api_key=os.environ["HF_TOKEN"],
)

# output is a PIL.Image object
image = client.text_to_image(
    "Baby Yoda being super cute and running a financial advisory office",
    model="black-forest-labs/FLUX.1-dev",
)

filename = "grogu_today.png"
image.save(filename)
print(f"Saved {filename}")

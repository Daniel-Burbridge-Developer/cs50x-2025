import json
import os

CONFIG_FILE = "config.json"


def load_config():
    if not os.path.exists(CONFIG_FILE):
        return {}
    with open(CONFIG_FILE, "r") as f:
        return json.load(f)


def save_config(config):
    with open(CONFIG_FILE, "w") as f:
        json.dump(config, f, indent=4)
    print("Configuration saved!")


def main():
    print("---Image-Generator Management Console---")
    config = load_config()

    while True:
        print("\nOptions:")
        print("  1. Update Models")
        print("  2. Options")
        print("  3. Schedule")
        print("  4. Save & Exit")

        choice = input("Select an option (1-4): ")

        if choice == "1":
            update_model(config)
        elif choice == "2":
            update_options(config)
        elif choice == "3":
            update_schedule(config)
        elif choice == "4":
            save_config(config)
            print("Saving...")
            print("Complete - Exiting Config")
            break
        else:
            print("Invalid choice.")


def update_model(config):
    while True:
        print("\n Model Options")
        print("  1. Edit Model Preferences")
        print("  2. Add New Model")
        print("  3. Back")

        choice = input("Select an option (1-3): ")
        if choice == "1":
            edit_model_preferences(config)
        elif choice == "2":
            add_new_model(config)
        elif choice == "3":
            print("Returning to main menu...")
            break
        else:
            print("Invalid choice.")


def edit_model_preferences(config):
    # I should sort this by preference, before printing - but I'll do this for now.
    for i, model in enumerate(config["models"].values()):
        print(
            f"  {i + 1}. Update {model['alias']} current preference {model['preference']}"
        )
    print(f"  {int(len(config['models']) + 1)}. Exit")

    while True:
        choice = input(f"Select an option (1-{int(len(config['models'])) + 1}): ")

        if int(choice) < int(len(config["models"]) + 1):
            # update model
            print("updating model")
        elif int(choice) == int(len(config["models"]) + 1):
            print("exiting update")
            break
        else:
            print("Invalid input")

    return


def add_new_model(config):
    # I should prevent duplicate Alias's not just keys, but I'm not sure how right now.
    new_model = input("What is your new model? ")

    if new_model not in config["models"]:
        alias = input("alias: ")
        # ensure this swaps preference with a different one, or just make the new model the least preference by default
        preference = input("preference: ")
        # this should probably be limited to URL and API
        call_method = input("call method:")
        token = input("WARNING - THIS WILL BE STORED IN PLAIN TEXT - \n token:")
        # save this somehow
        print("Model added")
    else:
        print("Already have model in list")

    return


def update_options(config):
    return


def update_schedule(config):
    return


if __name__ == "__main__":
    main()

from config_manager import ConfigManager
from main import run_program


def main():
    print("---Image-Generator Management Console---")
    config = ConfigManager()

    while True:
        print("\nOptions:")
        print("  1. Update Models")
        print("  2. Options (Not Implemented)")
        print("  3. Schedule (Not Implemented)")
        print("  4. Exit")
        print("  5. Start Program")

        choice = input("Select an option (1-5): ")

        if choice == "1":
            update_model(config)
        elif choice == "2":
            update_options(config)
        elif choice == "3":
            update_schedule(config)
        elif choice == "4":
            print("Exiting Config")
            break
        elif choice == "5":
            start_program_execution()
        else:
            print("Invalid choice.")


def start_program_execution():
    print("\nStarting program... Press Ctrl+C to stop and return to menu.")
    try:
        run_program()
    except KeyboardInterrupt:
        print("\nStopping program and returning to menu...")
    except Exception as e:
        print(f"\nAn error occurred: {e}")
        input("Press Enter to continue...")


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
            break
        else:
            print("Invalid choice.")


def edit_model_preferences(config):
    models = config.get_models()
    if not models:
        print("No models found.")
        return

    # Create a list for indexed access
    model_list = list(models.items())

    for i, (name, data) in enumerate(model_list):
        print(
            f"  {i + 1}. Update {data.get('alias', name)} (Current Preference: {data.get('preference', 'N/A')})"
        )
    print(f"  {len(model_list) + 1}. Back")

    try:
        choice = int(input(f"Select an option (1-{len(model_list) + 1}): "))
        if 1 <= choice <= len(model_list):
            selected_model_name = model_list[choice - 1][0]
            selected_model_data = model_list[choice - 1][1]

            new_pref = input(
                f"Enter new preference for {selected_model_data.get('alias', selected_model_name)}: "
            )
            if new_pref.isdigit():
                success, msg = config.update_preference(
                    selected_model_data.get("alias"), new_pref
                )
                print(msg)
            else:
                print("Invalid preference. Must be a number.")
        elif choice == len(model_list) + 1:
            return
        else:
            print("Invalid choice.")
    except ValueError:
        print("Invalid input.")


def add_new_model(config):
    print("\nAdding New Model")
    name = input("Model unique name (key): ")
    if not name:
        return

    alias = input("Alias: ")
    preference = input("Preference (number): ")
    if not preference.isdigit():
        print("Preference must be a number.")
        return

    call_method = input("Call Method (URL/API): ")
    token = input("Token (stored in plain text, use warning): ")

    success, msg = config.add_model(name, alias, preference, call_method, token)
    print(msg)


def update_options(config):
    print("Options update not implemented yet.")
    return


def update_schedule(config):
    print("Schedule update not implemented yet.")
    return


if __name__ == "__main__":
    main()

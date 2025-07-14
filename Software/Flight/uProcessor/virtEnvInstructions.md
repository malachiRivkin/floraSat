Here is how to set up a virtual environment in Python:
1. Create a virtual environment
Open your terminal or command prompt.
Navigate to your project directory using the cd command.
Run the command python -m venv <environment_name>. Replace <environment_name> with your desired name for the virtual environment (e.g., venv, myenv).
2. Activate the virtual environment
On Windows:
Run the command <environment_name>\Scripts\activate.
On macOS and Linux:
Run the command source <environment_name>/bin/activate.
Once activated, your terminal prompt will display the name of your virtual environment in parentheses, indicating that it is active.
3. Install packages
With the virtual environment activated, use the pip install <package_name> command to install packages. These packages will be installed only within your virtual environment and will not affect your global Python installation.
For example, pip install requests installs the requests library.
4. Deactivate the virtual environment
When you are done working in the virtual environment, run the command deactivate to return to your global Python environment.
Important Notes:
It is good practice to create a virtual environment for each Python project to avoid dependency conflicts between projects.
The virtual environment folder is usually named venv, env, or .venv.
You can use the command pip freeze > requirements.txt to save a list of installed packages in your virtual environment to a requirements.txt file. You can then use pip install -r requirements.txt to install the same packages in another virtual environment.
If you are using Visual Studio Code, it can automatically detect and use the virtual environment for your project.virtenv
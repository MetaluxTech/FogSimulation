import subprocess
import os
def runSimulation():
        print("Running the simulation...")
        os.chdir("C:/Users/mohsal/Desktop/app/metalux/fog/simulations/fogsim6")
        bash_path = "C:/Program Files/Git/bin/bash.exe"
        script_path = "C:/Users/mohsal/Desktop/app/metalux/fog/simulations/fogsim6/runy.sh"
        result = subprocess.run([bash_path, script_path])
        if result.returncode == 0:
            print("Script ran successfully!")
        else:
            print(f"Script exited with code {result.returncode}")


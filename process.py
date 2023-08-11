import subprocess
import os

def run_simulation(omnet_path,project_path, ini_file, network):
   
    command = [f"{omnet_path}", "-n", ".", "-u", "Cmdenv", "-c", network, "-f", ini_file]
    result = subprocess.run(command, cwd=project_path, capture_output=True, text=True)

    # Print the result to the console
    print(f'out {result}')
    if result.stderr:
        print(result.stderr)
        print(f'errors {result.stderr}')
        
        

# Run the simulation
 
omnet_path = "D:/fog_simulator/omnetpp-4.6/bin/opp_run.exe"  
project_path = 'D:/fog1/fogsim1/'
ini_file = 'omnetpp.ini'
network = 'network.ned'
run_simulation(omnet_path,project_path, ini_file, network)

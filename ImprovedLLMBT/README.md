## IntentionReasoning:  
First, set the contents of Demonstrations.txt, Prompts.txt, and SemanticMap.xml as the context of your selected LLM (such as ChatGPT4).  
A quick way is to copy these contents directly to the LLM.  
Second, input the instructions in Case.txt to the LLM.  
If the instructions are incomplete, refer to the cases in Guidance.txt to guide LLM to ask questions to the user.  
## Run BTAdaptiveUpdate in Linux:  
The BTAdaptiveUpdate algorithm is developed based on https://btirai.github.io/youbot.  
1. Install Dependencies:  
    &emsp;Open terminal:  
         &emsp; &emsp;sudo apt-get install build-essential libgl1-mesa-dev python3-tk qtdeclarative5-dev
2. Download & install V-REP(CoppeliaSim):  
    &emsp;https://www.coppeliarobotics.com/previousVersions (Recommended version: 3.6.2)  
3. Compile BTAdaptiveUpdate:  
    &emsp;cd BTAdaptiveUpdate  
    &emsp;mkdir build & cd build  
    &emsp;cmake ..  
    &emsp;make  
4. Run V-REP:  
    &emsp;Open terminal:  
        &emsp;&emsp;go to V-REP directory  
        &emsp;&emsp;./vrep.sh  
        &emsp;&emsp;File->Open Scene:  
        &emsp;&emsp;BTAdaptiveUpdate/Dataset/house_serive_dataset_cargos.ttt (or house_serive_dataset_foods.ttt).  
5. Run BTAdaptiveUpdate:  
    &emsp;Open terminal:  
        &emsp;&emsp;cd BTAdaptiveUpdate/build  
        &emsp;&emsp;./BT  
        &emsp;&emsp;File->Load:  
        &emsp;&emsp;Load a corressponding initial BT (cargos.xml or foods.xml)  
        &emsp;&emsp;Press Play icon  
6. You can modify the initial BT or the position of objects in the dataset  

# LLM-BT
The BTs-Update algorithm is developed based on https://btirai.github.io/youbot.  
## Run in Linux:  
1. Install Dependencies:  
    &emsp;Open terminal:  
         &emsp; &emsp;sudo apt-get install build-essential libgl1-mesa-dev python3-tk qtdeclarative5-dev
2. Download & install V-REP(CoppeliaSim):  
    &emsp;https://www.coppeliarobotics.com/previousVersions (Recommended version: 3.6.2)  
3. Compile BTs_Update:  
    &emsp;cd LLM_BT/BTs_Update  
    &emsp;mkdir build & cd build  
    &emsp;cmake ..  
    &emsp;make  
4. Run V-REP:  
    &emsp;Open terminal:  
        &emsp;&emsp;go to V-REP directory  
        &emsp;&emsp;./vrep.sh  
        &emsp;&emsp;File->Open Scene:  
        &emsp;&emsp;LLM_BT/LLM_BT_Scene.ttt  
        &emsp;&emsp;Press Play icon  
5. Run Parser & BTs_Update:  
    &emsp;Open terminal:  
         &emsp;&emsp;cd LLM_BT/Parser  
         &emsp;&emsp;python3 parser.py  

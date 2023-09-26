# LLM-BT
The BTs-Update algorithm is developed based on https://btirai.github.io/youbot.

Run in Linux:
    1. Install Dependencies:
        Open terminal:
            sudo apt-get install build-essential libgl1-mesa-dev python3-tk qtdeclarative5-dev
    2. Download & install V-REP(CoppeliaSim):
        https://www.coppeliarobotics.com/previousVersions (Recommended version: 3.6.2)
    3. Compile BTs_Update:
        cd LLM_BT/BTs_Update
        mkdir build & cd build
        cmake ..
        make
    4. Run V-REP:
        Open terminal:
            go to V-REP directory
            ./vrep.sh
            File->Open Scene:
                LLM/BT/LLN_BT_Scene.ttt
            Press Play icon
    5. Run Parser & BTs_Update:
        Open terminal:
            cd LLM_BT/Parser
            python3 parser.py

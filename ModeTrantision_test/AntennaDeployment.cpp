#include "AntennaDeployment.h"
#include "Arduino.h"


AntennaDeployment::AntennaDeployment()
{

}

void AntennaDeployment::startUp()
{
    while(isOpen()==false){
    ioExpander.setPin(AntennaDeploymentPin,HIGH);
    counter++;
    if(counter>300000){//NOTE 無限ループ対策　脱出の基準はもっと大きくしても良い
        break;
    }
    }
    ioExpander.setPin(AntennaDeploymentPin,LOW);
}


bool AntennaDeployment::isOpen(){
    //NOTE:ハードの関係で電源マイコンと逆で閉じていたらtrue、開いてたらfalseを出す
    if(ioExpander.read(AntennaDeploymentConfirmPin) == true){
        return false;
    }
    else{
        return true;
    }
}
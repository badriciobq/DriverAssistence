// Created by Mauricio Silva on 28/10/15.

#ifndef DRIVER_ASSISTENCE_ILISTENERS_H
#define DRIVER_ASSISTENCE_ILISTENERS_H

#include <set>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "Debug.h"

/* Maurício José da Silva <badriciobq@gmail.com>
 * Classe para notificar a parte nativa quando uma imagem for recebida para ser processada
 * */
class IListenerImage{
  public:
    virtual void handleNotification(cv::Mat &mSrc)=0;
};

class NotifierImage{

  public:
    NotifierImage(){
    }

    virtual ~NotifierImage() {
        mListener.clear();
    }

    virtual void notify(cv::Mat mSrc){
        std::set<IListenerImage *>::iterator it;
        for(it = mListener.begin(); it != mListener.end(); ++it){
            ((IListenerImage*) *it)->handleNotification(mSrc);
        }
    }

    virtual void registerListener(IListenerImage *i){
        mListener.insert(i);
    }

    virtual void unregisterListener(IListenerImage *i){
        std::set<IListenerImage *>::const_iterator iter = mListener.find(i);
        if(iter != mListener.end()){
            mListener.erase(iter);
        }else{
            LOGE("Could not unregister listener!");
        }
    }

  private:
    std::set<IListenerImage *> mListener;
};


/* Maurício José da Silva <badriciobq@gmail.com>
 * Classe para notificar a parte nativa quando uma imagem for processada, o resultado computado
 * e um valor estiver pronto para ser enviado para o java
 * */

class IListenerValue{
  public:
    virtual void handleNotification();
};


class NotifierValue{
  protected:
    virtual void notify(){
        std::set<IListenerValue *>::const_iterator it;
        for( it = mListener.begin();  it != mListener.end(); ++it){
            ((IListenerValue*) *it)->handleNotification();
        }
    }

  public:
    NotifierValue(){
    }

    ~NotifierValue() {
        mListener.clear();
    }

    virtual void registerListener(IListenerValue *i){
        mListener.insert(i);
    }

    virtual void unregisterListener(IListenerValue *i){
        std::set<IListenerValue *>::const_iterator iter = mListener.find(i);
        if(iter != mListener.end()){
            mListener.erase(iter);
        }else{
            LOGE("Could not unregister listener!");
        }
    }

  private:
    std::set<IListenerValue *> mListener;
};


#endif //DRIVER_ASSISTENCE_ILISTENERS_H

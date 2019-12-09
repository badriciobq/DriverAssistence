#ifndef DRIVER_ASSISTENCE_PROCESSOR_H
#define DRIVER_ASSISTENCE_PROCESSOR_H

#include <cpu-features.h>
#include <pthread.h>
#include <jni.h>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <deque>

#include "IListeners.h"

class Processor : public IListenerImage {

public:
    ~Processor();
    bool Initialize(JNIEnv *env, jobject obj);
    bool Finalize();

    static Processor *GetInstance(){
        if(!m_processorInstance){
            m_processorInstance = new Processor();
        }
        return m_processorInstance;
    }

    virtual void handleNotification(cv::Mat &mSrc);

private:
    // Default constructor in private block why this is a singleton class
    Processor();

    // Insere uma matriz no queue e notifica as threads
    void PushImage(cv::Mat &img);

    // Remove uma matriz do queue
    bool PopImage(cv::Mat &img);

    // Do Process of the image
    static void *doProcess(void *);

    bool EventN2J(int);

    // Auxiliar methods
    std::vector<cv::Vec3f> DetectCircles(cv::Mat &src);
    char * getTextFromImg(cv::Mat &src);
    void RGB_Zaklouta_2014(cv::Mat &src, cv::Mat &dst);


    // bool to control processing
    static bool isProcessing;

    // controll number frames persist (after 10 frames persist 1 frame to each 10)
    static int control_frame;

    // Guard a instance to this class
    static Processor *m_processorInstance;

    // sincronized access
    static const int BUFFER_SIZE = 15;
    static std::deque<cv::Mat> m_images;

    /*Pthread variables*/
    static int num_threads;
    static pthread_mutex_t m_img_mutex;
    static pthread_cond_t m_img_signal;
    static pthread_attr_t m_img_attr;
    static pthread_t *m_threads;


    /* Calback from Native*/
    static jobject m_jObject;
    static jclass m_eventClass;
    static jmethodID m_onCallBackID;
    static JavaVM *m_javaVM;

};

#endif //DRIVER_ASSISTENCE_PROCESSOR_H

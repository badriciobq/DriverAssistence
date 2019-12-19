#include "adas.h"

#include "Debug.h"
#include "Monitor.h"
#include "Processor.h"

#include <sstream>
#include <string>



JavaVM *s_Jvm;
MonitorBase *m_monitor = NULL;
static Processor *m_processImage = NULL;
bool isInitialized = false;


JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    if(!vm)
    {
        s_Jvm = vm;
    }

    return JNI_VERSION_1_6;
}


/*
 * Class:     com_example_adas_MainActivity
 * Method:    ProcessImage
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_example_adas_MainActivity_ProcessImage
  (JNIEnv *env, jobject, jlong src)
  {
    // Converte os endereços das matrizes retornadas pela camada java em objetos do c++.
    cv::Mat &mSrc = *((cv::Mat *) src);

    int x, y, width, height;

    int rows = mSrc.rows;
    int cols = mSrc.cols;

    // Define a região de interesse
    x = cols/2+cols*0.2;
    y = rows*0.1;
    width = cols-x;
    height = rows-y-rows*0.25;
    cv::Rect roi = cv::Rect(x*0.9,y,width, height);


    if(m_monitor) {
        m_monitor->notify( mSrc(roi).clone() );
    }else{
        LOGE("There isn't a monitor instantiated");
    }

    cv::rectangle(mSrc, roi, cv::Scalar(0,255,0), 1);

    cv::line(mSrc, cv::Point(0,(rows/2)+y), cv::Point(cols,(rows/2)+y), cv::Scalar(255,0,0), 1);
    cv::circle(mSrc, cv::Point((cols/2),(rows/2)+y), 10, cv::Scalar(255,0,0), 1);

    return;
  }

/*
 * Class:     com_example_adas_MainActivity
 * Method:    Initialize
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_example_adas_MainActivity_Initialize
  (JNIEnv * env, jobject obj)

  {
    if(isInitialized) {
        return JNI_TRUE;
    }

    m_monitor = MonitorBase::GetInstance();
    if (!m_monitor)
    {
        LOGE("Could not get monitor instance");
        return JNI_FALSE;
    }

    m_processImage = Processor::GetInstance();
    if(!m_processImage)
    {
        LOGE("Could not get processor instance");
        return JNI_FALSE;
    }

    m_processImage->Initialize(env, obj);

    m_monitor->registerListener(m_processImage);

    isInitialized = true;

    return JNI_TRUE;

  }

/*
 * Class:     com_example_adas_MainActivity
 * Method:    Finalize
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_example_adas_MainActivity_Finalize
  (JNIEnv * env, jobject obj)
  {
    if(m_monitor)
    {
        m_monitor->unregisterListener(m_processImage);
    }

    if(m_processImage)
    {
        m_processImage->Finalize();
    }

    isInitialized = false;

    return JNI_TRUE;
  }

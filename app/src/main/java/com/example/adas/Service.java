package com.example.adas;


public class Service {

    private static IListener m_listener;

    public Service(IListener iListener){
        m_listener = iListener;
    }

    public static void onCallBack(int value){
        m_listener.onEvent(value);
    }
}

package com.example.adas;

import android.Manifest;
import android.content.Context;
import android.content.pm.PackageManager;
import android.media.MediaPlayer;
import android.os.Bundle;
import android.os.Environment;
import android.os.PowerManager;
import android.util.Log;
import android.view.SurfaceView;
import android.view.View;
import android.view.WindowManager;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import org.opencv.android.BaseLoaderCallback;
import org.opencv.android.CameraBridgeViewBase;
import org.opencv.android.CameraBridgeViewBase.CvCameraViewListener2;
import org.opencv.android.LoaderCallbackInterface;
import org.opencv.android.OpenCVLoader;
import org.opencv.core.Mat;

import java.io.File;


public class MainActivity extends AppCompatActivity implements CvCameraViewListener2, ActivityCompat.OnRequestPermissionsResultCallback, IListener {
    private static final String  TAG = "DriverAssist/TRSign";

    private static final int PERMISSION_ALL = 1;

    String[] PERMISSIONS = {
            android.Manifest.permission.WRITE_EXTERNAL_STORAGE,
            Manifest.permission.WAKE_LOCK,
            android.Manifest.permission.CAMERA
    };


    private static int last_value = 0;

    private CameraBridgeViewBase mOpenCvCameraView;
    private boolean isNativeInitialized = false;
    private Service m_listener;
    private TextView tx;

    protected PowerManager.WakeLock mWakeLock;



    private BaseLoaderCallback  mLoaderCallback = new BaseLoaderCallback(this) {
        @Override
        public void onManagerConnected(int status) {
            switch (status) {
                case LoaderCallbackInterface.SUCCESS:
                {
                    Log.i(TAG, "OpenCV loaded successfully");

                    // Load native library after(!) OpenCV initialization
                    System.loadLibrary("adas");

                    // Initialize the native listeners
                    isNativeInitialized = Initialize();

                    mOpenCvCameraView.enableView();
                } break;
                default:
                {
                    super.onManagerConnected(status);
                } break;
            }
        }
    };

    @Override
    public void onCameraViewStarted(int width, int height) { }

    @Override
    public void onCameraViewStopped() { }

    @Override
    public Mat onCameraFrame(CameraBridgeViewBase.CvCameraViewFrame inputFrame) {

        Mat src = inputFrame.rgba();

        if(isNativeInitialized) {
            ProcessImage(src.getNativeObjAddr());
        }else{
            Log.d(TAG, "Could not initialize libs!");
            return src;
        }

        return src;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        setContentView(R.layout.activity_main);

        mOpenCvCameraView = (CameraBridgeViewBase) findViewById(R.id.image_view);
        mOpenCvCameraView.setVisibility(SurfaceView.VISIBLE);
        mOpenCvCameraView.setCvCameraViewListener(this);

        m_listener = new Service(this);
        tx = (TextView) findViewById(R.id.textView);

        // BEGIN_INCLUDE(startCamera)
        // Check if the Camera permission has been granted
        if (hasPermissions(this, PERMISSIONS)) {
            // Permission is already available, start camera preview

            startCamera();

        } else {
            // Permission is missing and must be requested.
            requestAllPermissions();
        }
        // END_INCLUDE(startCamera)

    }


    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions,
                                           @NonNull int[] grantResults) {

        if (requestCode == PERMISSION_ALL) {
            if (grantResults.length == 3 && ( grantResults[0] == PackageManager.PERMISSION_GRANTED ) ) {
                // Permission has been granted. Start camera preview Activity.
                startCamera();

            } else {
                // Permission request was denied.
                Toast.makeText(MainActivity.this, "Usuário recusou a permissão", Toast.LENGTH_LONG);
            }
        }
        // END_INCLUDE(onRequestPermissionsResult)
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        if (mOpenCvCameraView != null)
            mOpenCvCameraView.disableView();
    }

    private void startCamera(){

        if (!OpenCVLoader.initDebug()) {
            Log.d(TAG, "Internal OpenCV library not found. Using OpenCV Manager for initialization");
            OpenCVLoader.initAsync(OpenCVLoader.OPENCV_VERSION_3_0_0, this, mLoaderCallback);
        } else {
            Log.d(TAG, "OpenCV library found inside package. Using it!");
            mLoaderCallback.onManagerConnected(LoaderCallbackInterface.SUCCESS);
        }
    }



    private void requestAllPermissions() {
        ActivityCompat.requestPermissions(this, PERMISSIONS, PERMISSION_ALL);
    }

    private static boolean hasPermissions(Context context, String... permissions) {
        if (context != null && permissions != null) {
            for (String permission : permissions) {
                if (ActivityCompat.checkSelfPermission(context, permission) != PackageManager.PERMISSION_GRANTED) {
                    return false;
                }
            }
        }
        return true;
    }

    @Override
    public void onEvent(final int value) {

        runOnUiThread(new Runnable() {
            @Override
            public void run() {

                if(value != last_value) {
                    tx.setVisibility(View.VISIBLE);
                    tx.setText(Integer.toString(value));

                    MediaPlayer mp = MediaPlayer.create(getApplicationContext(), R.raw.success);

                    if (!mp.isPlaying())
                        mp.start();

                    mp.setOnCompletionListener(new MediaPlayer.OnCompletionListener() {
                        @Override
                        public void onCompletion(MediaPlayer mp) {
                            mp.release();
                        }
                    });

                    last_value = value;
                }
            }
        });
    }

    BaseLoaderCallback mCallBack = new BaseLoaderCallback(this) {
        @Override
        public void onManagerConnected(int status) {
            switch (status){
                case BaseLoaderCallback.SUCCESS:
                {
                    Log.i(TAG, "OpenCV loaded successfully");
                    mOpenCvCameraView.enableView();
                    break;
                }
                default:
                {
                    super.onManagerConnected(status);
                    break;
                }
            }
        }
    };


    public native void ProcessImage(long src);
    public native boolean Initialize();
    public native boolean Finalize();


}

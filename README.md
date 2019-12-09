# README

Aplicativo compatível com:
 - Android SDK API-29
 - NDK 16.1.4479499
 - [OpencvForAndroid 3.0.0](https://sourceforge.net/projects/opencvlibrary/files/opencv-android/3.0.0/OpenCV-3.0.0-android-sdk-1.zip/download)
 - Tesseract OCR [tessdata 3.0.2](https://sourceforge.net/projects/tesseract-ocr-alt/files/tesseract-ocr-3.02.eng.tar.gz/download)



## Installation

 - Importe o projeto no AndroidStudio (File > New > Import Project)
 - Importe o Opencv 3.0.0 como um módulo (File > New > Import Module)
 - Adicione o Opencv como dependência do ADAS (Botão direito sobre o projeto > Open Modulo Settings > dependencies > Add Module)
 - Baixe os dados do tesseract no link acima e coloque no celular no diretório (/sdcard/tessdata/)
 - Configure o arquivo Android.MK para que o OPENCV\_ROOT corresponda com o lugar em que você baixou o opencv 3.0.0
 - Crie o diretório no android /sdcard/DriverAssistence/Plates
 - Make Construir o projeto e instalar no telefone. 
 
## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License
[MIT](https://choosealicense.com/licenses/mit/)

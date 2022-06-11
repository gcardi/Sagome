# Sagome
Applicazione per il pilotaggio delle sagome del poligono di tiro per la "Federazione Sammarinese Tiro a Segno".

Clonare il repository usando 'recurse-submodules'

```
git clone --recurse-submodules https://github.com/gcardi/Sagome.git
```

Necessita di FFTW per Windows (solo le DLL) (http://www.fftw.org/download.html)

La struttura delle cartelle deve essere la seguente:

```
├───FFTW
│   ├───fftw-3.3-dll32 (dll qui)
│   └───fftw-3.3-dll64 (dll qui)
├───Libs
│   ├───Win32
|   |     libfftw3-3.lib (import library generata con implib)
│   └───Win64
|         ibfftw3-3.a (import library generata con mkexp)
└───Risorse
    └───MP3 (estensione .wav, ma contengono media in formato MP3)
```

## Screenshots

<a href="https://ibb.co/t2yM1MP"><img src="https://i.ibb.co/n1hsKs8/Sagome-1.png" alt="Sagome-1" border="0"></a>

<a href="https://ibb.co/0fkxHC5"><img src="https://i.ibb.co/brxkcst/Sagome-2.png" alt="Sagome-2" border="0"></a>

<a href="https://ibb.co/Cv2cV76"><img src="https://i.ibb.co/L65F9tr/Sagome-3.png" alt="Sagome-3" border="0"></a>

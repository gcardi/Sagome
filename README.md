# Sagome
Programma pilotaggio sagome per Federazione Sammarinese Tiro a Segno

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


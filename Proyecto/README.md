Alejandro Martinez - 21430

Arturo Argutea - 21527

## OpenMp:
| Enabled | Disabled
|:--:|:--:|
| ![alt text](image.png) | ![alt text](image-3.png) |

# Demo


REALTIME:
[Demo Video](Demo.mp4)
![alt text](image-2.png)

HQ:
[Demo Video](Demo-2.mp4)
![alt text](image-1.png)

Defaults:
```console
--voxel-size 0.015 --sphere-display-mult 1.0 --grid-size 270 150 --iterations 4.0 --render-scale 0.25 --openmp 1
```

# 1080p
~60-70 fps (FHD Screen)
```console
./Cpp.exe --voxel-size 0.03 --sphere-display-mult 1.15 --grid-size 135 75 --iterations 4.0 --render-scale 0.25 --openmp 1
```

~30-35fps (FHD Screen)
```console
./Cpp.exe --voxel-size 0.015 --sphere-display-mult 1.45 --grid-size 270 150 --iterations 4.0 --render-scale 0.2 --openmp 1
```

~5-10fps (FHD Screen)
```console
./Cpp.exe --voxel-size 0.0075 --sphere-display-mult 1.5 --grid-size 540 300 --iterations 6 --render-scale 0.25 --openmp 1
```


Half Resolution
```console
./Cpp.exe --voxel-size 0.03 --grid-size 135 75 --iterations 4.0 --render-scale 0.5 --sphere-display-mult 1.0 --openmp 1 
```

Native Resolution
```console
./Cpp.exe --voxel-size 0.05 --grid-size 50 20 --iterations 4.0 --render-scale 1.0 --sphere-display-mult 1.0 --openmp 1 
```
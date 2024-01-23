import time
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib import style
from ctypes import *
SAMPLE_SIZE = 1000
class QF_IFC(Structure):
    _fields_ = [
        ("Fx1", c_int16),
        ("Fy1", c_int16),
        ("Fz1", c_int16),
        ("Fx2", c_int16),
        ("Fy2", c_int16),
        ("Fz2", c_int16),
        ("Fx3", c_int16),
        ("Fy3", c_int16),
        ("Fz3", c_int16),
        ("Fx4", c_int16),
        ("Fy4", c_int16),
        ("Fz4", c_int16),
        ("Fx", c_int32),
        ("Fy", c_int32),
        ("Fz", c_int32),
        ("Mx", c_int32),
        ("My", c_int32),
        ("Mz", c_int32),
        ]

samples_array = (QF_IFC * SAMPLE_SIZE)
qfcal = cdll.LoadLibrary("C:\code\CBA\CBAlib\\build32\src\calibrationRig\Release\calibrationRig.dll")

qf_init = qfcal.QuestFitCalibrationRig_Init
qf_start = qfcal.QuestFitCalibrationRig_StartRawDataMode
qf_stop = qfcal.QuestFitCalibrationRig_StopDataMode
qf_get = qfcal.QuestFitCalibrationRig_GetSamples
qf_get.argtypes = [c_size_t, samples_array, POINTER(c_size_t)]
res =qf_init()
print(f"INIT {res}")
time.sleep(2)
res = qf_start()
samples = samples_array()
print(f"START {res}")
style.use("fivethirtyeight")
fig = plt.figure()
ax1 = fig.add_subplot(1,1,1)
try:
    while True:
        num_samples = c_size_t(0)
        qf_get(SAMPLE_SIZE, samples,byref(num_samples))
        if num_samples.value > 0:
            print(f"GOT {num_samples.value} SAMPLES")
            break
        time.sleep(1)
except KeyboardInterrupt:
    # Shutdown
    res =qf_stop()
    print(f"STOP {res}")
# Allocate sample structure 
z_samples = []

def animate(i):
    global z_samples
    try:
        while True:
            num_samples = c_size_t(0)
            res =qf_get(SAMPLE_SIZE, samples,byref(num_samples))
            if res == 0 and num_samples.value > 0:
                # Chart them
                print(f"GOT {num_samples.value} SAMPLES")
                # Copy the samples out
                for sample in samples:
                    z_samples.append(sample.Fz1)
                if len(z_samples) > 20000:
                    z_samples = z_samples[-20000:-1]
                
                ax1.clear()
                ax1.plot(z_samples)
                break
            time.sleep(0.02)
    except KeyboardInterrupt:
        # Shutdown
        res =qf_stop()
        print(f"STOP {res}")
ani = animation.FuncAnimation(fig, animate, interval=(SAMPLE_SIZE / 2000)*500)
try:
    plt.show()
except KeyboardInterrupt:
    pass
finally:
    # Shutdown
    res =qf_stop()
    print(f"STOP {res}")
#priemera red neuronal(modelo 1)
import tensorflow as tf
import numpy as np
import keras
from keras import layers
import matplotlib.pyplot as plt


celsius = np.array([-40, -10, 0, 8, 15, 22, 38], dtype=float)
fahrenheit = np.array([-40, 14, 32, 46, 59, 72, 100], dtype=float)

#

capa = keras. layers.Dense(units=1, input_shape=[1])
modelo = keras.Sequential([capa])

modelo.compile(
    optimizer= keras.optimizers.Adam(1),
    loss='mean_squared_error'
)
print('''
Entrenamiento
''')

historial = modelo.fit(celsius, fahrenheit, epochs=1000, verbose=False)
print('''
Modelo Entrenado
''')

print('''
Prediccion
''')

resultado = modelo.predict([200.0])
plt.xlabel("# Epoca")
plt.ylabel("Magnitud Perdida")
plt.plot(historial.history["loss"])
print()
print(capa.get_weights())
print("El resultado es " + str(resultado) + " fahrenheit")

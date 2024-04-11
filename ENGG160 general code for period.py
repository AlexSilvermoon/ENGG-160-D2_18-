import math
m1 =float(input('Enter the mass of the rod in kilograms (Note for the current model it is 0.006kg): '))
m2= float(input('Enter the mass attached in kilograms (Note for the current model it is 0.02155kg): '))
L = float(input('Enter the length of the rod in meters (Note for the current model it is 0.1897m): '))
theta = float(input('Enter the intial angle that the pendulum was displaced from the vertical: '))/180*math.pi
T4= float(input('What is the period from the sensor: ' ))
Mtotal = m1+m2 #total mass.
I = (1/3)*m1*L**2 + m2*L**2 #center of inertia from the pivot point.
Xcm = ( m1*(L/2) + m2*(L))/(Mtotal) #center of mass.
T1 = 2*math.pi*math.sqrt(L/9.81) # period using the small angle formula.
T2 = 2*math.pi*math.sqrt(I/(Mtotal*9.81*Xcm)) # period using the moment of inertia.
T3 = T2*(1 + 1/16*theta**2+ 11/3072*theta**4+ 173/737280*theta**6+ 22931/1321205760*theta**8)
print('The center of mass is:', Xcm)
print('The period using small angle approximation is:', T1)
print('The period using inertia is:', T2)
print('The period using inertia and large angle is:', T3)
g1 = L/(T1**2/(4*math.pi**2)) # Gravity using small angle period, set to be 9.81
g2 = I/(Mtotal*Xcm*T2**2/(4*math.pi**2)) # Gravity using inertia, set to be 9.81
g3 = L/(T4**2/(4*math.pi**2)) # Gravity using sensor
print('The acceleration due to gravity is:', g1)
print('The acceleration due to gravity using inertia is:', g2)
print('The acceleration due to gravity using the sensor is:', g3)
print('Percentage of error between the periods:', abs(100-T3/T4*100))
print('Percentage of error between the acceleration due to gravitys:', abs(100-g3/g2*100))

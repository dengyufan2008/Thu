# Week5 Homework

By Deng Yufan.

## 1. Bloch Sphere

a. We have $|\psi\rangle = \cos \frac{\pi/3}{2} |0\rangle+\sin \frac{\pi/3}{2} |1\rangle$, so $\theta=\pi/3$, $\phi=0$, $\vec r = (\frac{\sqrt 3}{2}, 0, \frac{1}{2})$.

b. $H|\psi\rangle=\frac{\sqrt 6+\sqrt 2}{4}|0\rangle+\frac{\sqrt 6-\sqrt 2}{4}|1\rangle$, $T|\psi\rangle=\frac{\sqrt 3}{2}|0\rangle+e^{i\pi/4}\frac{1}{2}|1\rangle$.

## 2. Evolution

a. We have $\frac{\text{d}}{\text{d}t}\alpha(t)=\frac{\omega}{i}\alpha(t)$, $\frac{\text{d}}{\text{d}t}\beta(t)=-\frac{\omega}{i}\beta(t)$, so $|\psi(t)\rangle=\frac{e^{-i\omega t}|0\rangle+e^{i\omega t}|1\rangle}{\sqrt 2}$.

b. We have $|\psi(t)\rangle=\frac{e^{-i\omega t}|0\rangle+e^{i\omega t}|1\rangle}{\sqrt 2}=\frac{e^{-i\omega t}+e^{i\omega t}}{2}|+\rangle+\frac{e^{-i\omega t}-e^{i\omega t}}{2}|-\rangle$. So $P(+)=(\frac{e^{-i\omega t}+e^{i\omega t}}{2})^2=\cos^2(\omega t)$, $P(-)=\sin^2(\omega t)$. When $t=0$, we have $P(+)=1$, $P(-)=0$.

## 3. Entanglement

a. We have $|a_0b_0+a_0b_1+a_1b_0-a_1b_1|=|a_0(b_0+b_1)+a_1(b_0-b_1)|$. Let $c_0=b_0+b_1$, $c_1=b_0-b_1$, we have $|a_0b_0+a_0b_1+a_1b_0-a_1b_1|=|a_0c_0+a_1c_1|$. If $b_0=b_1$, then we have $|c_0|=2$ and $c_1=0$; if $b_0 \ne b_1$, we have $|c_1|=2$ and $c_0=0$. So we have $|a_0c_0+a_1c_1| = |a_0c_0| + |a_1c_1|=2$. So this formula will always equal to 2. So the maximum is 2.

b. $|S|=\frac{1}{n}|\sum a_0^ib_0^i+\sum a_0^ib_1^i+\sum a_1^ib_0^i-\sum a_1^ib_1^i|=\frac{1}{n}|2n|=2$. So the maximum is 2.

c. We first calc measure matrix $A_0, A_1, B_0, B_1$, that is a $2 \times 2$ matrix s.t. $A_0a_0^{(+1)}=+1a_0^{(+1)}$, $A_0a_0^{(-1)}=-1a_0^{(-1)}$ and so on. This deduces $\langle\psi'|A_0|\psi'\rangle$ is the expectation when use basis $A_0$ to measure $|\psi'\rangle$.
  
  Let a basis $C$ s.t. $C^{(+1)}=\cos \theta|0\rangle+\sin \theta|1\rangle$, $C^{(-1)}=\sin \theta|0\rangle-\cos \theta|1\rangle$. Let measure matrix $C=\left(\begin{matrix}w & x \\ y & z\end{matrix}\right)$. Let $c=\cos \theta$, $s=\sin \theta$. We have $C=P\left(\begin{matrix}1 & 0 \\ 0 & -1\end{matrix}\right)P^{-1}$ where $P=\left(\begin{matrix}c & s \\ s & -c\end{matrix}\right)$ changes basis $C$ to standard basis. Easy to see $P^2=I$. So $C=\left(\begin{matrix}c^2-s^2 & 2cs \\ 2cs & -c^2+s^2\end{matrix}\right)=\left(\begin{matrix}\cos 2\theta & \sin 2\theta \\ \sin 2\theta & -\cos 2\theta\end{matrix}\right)$. Since $\theta = \pi/4$ and $\theta=\pi/8$ for $A_1$ and $B_0$, we have $A_1=\left(\begin{matrix}0 & 1 \\ 1 & 0\end{matrix}\right)$ and $B_0=\frac{1}{\sqrt 2}\left(\begin{matrix}1 & 1 \\ 1 & -1\end{matrix}\right)$.
  
  Let basis $D$ s.t. $D^{(+1)}=\cos \theta|0\rangle-\sin \theta|1\rangle$, $D^{(-1)}=\sin \theta|0\rangle+\cos \theta|1\rangle$. Then $P=\left(\begin{matrix}c & s \\ -s & c\end{matrix}\right)$, $PP^T=I$ and $D=\left(\begin{matrix}c^2-s^2 & -2cs \\ -2cs & -c^2+s^2\end{matrix}\right)=\left(\begin{matrix}\cos 2\theta & -\sin 2\theta \\ -\sin 2\theta & -\cos 2\theta\end{matrix}\right)$. Since $\theta=0$ and $\theta=\pi/8$ for $A_0$ and $B_1$, we have $A_0=\left(\begin{matrix}1 & 0 \\ 0 & -1\end{matrix}\right)$ and $B_1=\frac{1}{\sqrt 2}\left(\begin{matrix}1 & -1 \\ -1 & -1\end{matrix}\right)$.
  
  So we have $A_0=\left(\begin{matrix}1 & 0 \\ 0 & -1\end{matrix}\right)$, $A_1=\left(\begin{matrix}0 & 1 \\ 1 & 0\end{matrix}\right)$, $B_0=\frac{A_0+A_1}{\sqrt 2}$, $B_1=\frac{A_0-A_1}{\sqrt 2}$.
  
  We have $A_0 \otimes B_0$ is the measure matrix for the combination of Alice's basis and Bob's basis (notice that $\otimes$ means Kronecker product). So $E(A_0, B_0)=\langle\psi|(A_0 \otimes \frac{A_0+A_1}{\sqrt 2})|\psi\rangle=\frac{1}{\sqrt 2}\langle\psi|(A_0 \otimes A_0)|\psi\rangle+\frac{1}{\sqrt 2}\langle\psi|(A_0 \otimes A_1)|\psi\rangle$. So we need to calc $\langle\psi|(A_i \otimes A_j)|\psi\rangle$.
  
  Notice that $A_1|0\rangle=|1\rangle$, $A_1|1\rangle=|0\rangle$.
  
  We have $(A_0 \otimes A_0)|00\rangle=|00\rangle$, $(A_0 \otimes A_0)|11\rangle=(-1)^2|11\rangle=|11\rangle$, so $(A_0 \otimes A_0)|\psi\rangle=|\psi\rangle$, thus $\langle\psi|(A_0 \otimes A_0)|\psi\rangle=\lVert\psi\rVert=1$. We have $(A_0 \otimes A_1)|00\rangle=|01\rangle$ and $(A_0 \otimes A_1)|11\rangle=-|10\rangle$, so since the result and input is orthogonal, $\langle\psi|(A_0 \otimes A_1)|\psi\rangle=0$. Likewise, we have $\langle\psi|(A_1 \otimes A_0)|\psi\rangle=0$ and $(A_1 \otimes A_1)|\psi\rangle=|\psi\rangle$ thus $\langle\psi|(A_1 \otimes A_1)|\psi\rangle=1$.
  
  So $E(A_0, B_0)=\frac{1}{\sqrt 2}$, $E(A_0, B_1)=\frac{1}{\sqrt 2}$, $E(A_1, B_0)=\frac{1}{\sqrt 2}$, $E(A_1, B_1)=-\frac{1}{\sqrt 2}$.

d. We have $S=2\sqrt 2$, which is impossible if we assume predetermined.

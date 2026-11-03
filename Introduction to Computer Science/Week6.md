# Week6 Homework

By Deng Yufan.

## 1. Diffusion Transformer

### a.

We have

$$
\begin{aligned}
x_t &= \mathcal N(\sqrt{1-\beta_t} x_{t-1}, \beta_tI)
\\
&= \sqrt{1-\beta_t} x_{t-1} + \sqrt{\beta_t} y_t
\\
&= \sqrt{1-\beta_t} \mathcal N(\sqrt{\bar \alpha_{t-1}} x_0, (1-\bar \alpha_{t-1})I) + \sqrt{\beta_t} y
\\
&= \sqrt{1-\beta_t}[\sqrt{\bar \alpha_{t-1}} x_0 + \sqrt{1-\bar \alpha_{t-1}} z] + \sqrt{\beta_t} y
\\
&= \sqrt{\bar \alpha_t}x_0 + \sqrt{1-\beta_t}\sqrt{1-\bar \alpha_{t-1}}z + \sqrt{\beta_t}y
\\
&= \sqrt{\bar \alpha_t}x_0 + \sqrt{1-\bar \alpha_t}z,
\end{aligned}
$$

where $y, z \sim \mathcal N(0, 1)$, so $q(x_t \mid x_0)=\mathcal N(\sqrt{\bar \alpha_t}, (1-\bar \alpha_t)I)$.

### b.

We have

$$
\begin{aligned}
\text{KL}(q(x_{t-1} \mid x_t, x_0) \Vert p_\theta(x_{t-1} | x_t)) &= \text{KL}(\mathcal N(\tilde \mu_t, \tilde \beta_t I), \mathcal N(\mu_\theta(x_t, t), \tilde \beta_t I))
\\
&= \frac{1}{2\tilde \beta_t} \lVert \tilde \mu_t - \mu_\theta(x_t, t) \rVert^2
\\
&= \frac{1}{2\tilde \beta_t} \lVert \frac{\beta_t\sqrt{\bar \alpha_{t-1}}x_0+(1-\bar \alpha_{t-1})\sqrt{1-\beta_t}x_t}{1-\bar \alpha_t} - \frac{\sqrt{1-\bar \alpha_t}x_t-\beta_t\epsilon_\theta(x_t, t)}{\sqrt{1-\bar \alpha_t}\sqrt{1-\beta_t}} \rVert^2
\\
&= \frac{1}{2\tilde \beta_t} \lVert \frac{\beta_t \sqrt{\bar \alpha_t} x_0 -\beta_t x_t +\beta_t \sqrt{1-\bar \alpha_t}\epsilon_\theta(x_t, t)}{(1-\bar \alpha_t)\sqrt{1-\beta_t}} \rVert^2
\\
&= \frac{\beta_t^2}{2\tilde \beta_t} \lVert \frac{-\sqrt{1-\bar \alpha_t} \epsilon + \sqrt{1-\bar \alpha_t}\epsilon_\theta(x_t, t)}{(1-\bar \alpha_t)\sqrt{1-\beta_t}} \rVert^2
\\
&= \frac{\beta_t^2}{2\tilde \beta_t(1-\bar \alpha_t)(1-\beta_t)} \lVert \epsilon - \epsilon_\theta(x_t, t) \rVert^2.
\end{aligned}
$$

### c.

The video is $96 \times 256 \times 256$, so block is $24 \times 32 \times 32$, and patch is $12 \times 16 \times 16 = 3072$. So there are 3072 tokens.

### d.

$C_{\text{full}}=N^2=3072^2=9437184$.

$C_{\text{factorized}}=N(HW+F)=3072 \times 16 \times 16 + 3072 \times 12 = 823296$.

### e.

The objects in the video should be consistent and move continously, but if we generate all frames independently, the image model wont intend to give consistent result.

## 2. World Action Models

i. Video first. Since the method is first generating a future video and then extract action.

ii. Video first. Since the method is use DiT to predict information of future and get action.

iii. Action first. Since the method is use the action sequence to predict the future video.

iv. Joint. Since the method is predicting both action and video.

## 3. Tactile Sensing

### a.

We need to solve $u''(x)=-\frac{A}{T}\sin(\frac{2\pi}{\lambda} x)$.

We have $u'(x)=\frac{\lambda A}{2\pi T}\cos(\frac{2\pi}{\lambda} x) + C_1$.

Then $u(x) = \frac{\lambda^2 A}{4\pi^2 T} \sin(\frac{2\pi}{\lambda} x) + C_1x + C_2$.

We have $u(0)=u(L)=0$, so $C_1=-\frac{\lambda^2 A}{4\pi^2 TL}\sin(\frac{2\pi}{\lambda} L)$, $C_2=0$.

Thus $u(x) = \frac{\lambda^2 A}{4\pi^2 T} (\sin(\frac{2\pi}{\lambda} x) - \frac{x}{L}\sin(\frac{2\pi}{\lambda} L))$.

### b.

Let noise be $n(x) = \delta \sin(\frac{2\pi}{\lambda} (x-x_0))$, then we will calc $\tilde q(x) = -T(u(x)+n(x))'' = q(x) - Tn''(x)$, so error $\Delta q(x) = |Tn''(x)|=\frac{4\pi^2T\delta}{\lambda^2} |\sin(\frac{2\pi}{\lambda}(x-x_0))| \le \frac{4\pi^2T\delta}{\lambda^2}=0.2\pi^2 \text{N/mm} \approx 1.97 \text{N/mm}$.

### c.

We have $u''(x)=-\frac{1}{T}q(x)$, so $(u_b(x)-u_a(x))'' = -\frac{1}{T} \sin(\frac{2\pi}{\lambda} x)$, $u_b(x)-u_a(x)=\frac{\lambda^2}{4\pi^2 T} (\sin(\frac{2\pi}{\lambda} x) - \frac{x}{L}\sin(\frac{2\pi}{\lambda} L)) \le \frac{\lambda^2}{4\pi^2 T}  = \frac{5}{\pi^2} \mu\text{m} \approx 0.507 \mu\text{m}$ when $L=n\lambda/2$.

Since $0.507 < 1$, the camera cant tell them apart effectively.

### d.

i. Capacitive array, since piezoelectric sensor cant measure static force well.

ii. Magnetic sensor, since piezoresistive array cant measure shear force well.

iii. Vision-based tactile sensor, since EIT sensor has limited spatial resolution.

## Declaration of AI Use

I used AI to translate part of words, and acquired basic probability knowledge.

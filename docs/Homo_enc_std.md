# Homomorphic Encryption Standard

[toc]

Martin Albrecht, Melissa Chase, Hao Chen, Jintai Ding, Shafi Goldwasser, Sergey Gorbunov, Shai Halevi, Jeffrey Hoffstein, Kim Laine, Kristin Lauter, Satya Lokam, Daniele Micciancio, Dustin Moody, Travis Morrison, Amit Sahai, Vinod Vaikuntanathan

November 21, 2018

We met as a group during the Homomorphic Encryption Standardization Workshop on July 13-14, 2017, hosted at Microsoft Research in Redmond, and again during the second workshop on March 15-16, 2018 in MIT. Researchers from around the world represented government, industry, and academia. There are several research groups around the world who have made libraries for general-purpose homomorphic encryption available for applications and general-purpose use. Some examples include [SEAL], [HElib], [PALISADE], [cuHE], [cuFHE], [NFLlib], [HEAAN], and [TFHE]. Most general-purpose libraries for homomorphic encryption implement schemes that are based on the ring learning-with-error (RLWE) problem, and many of them displayed common choices for the underlying rings, error distributions, and other parameters.
我们在 2017 年 7 月 13 日至 14 日在雷德蒙德的 Microsoft Research 举办的同态加密标准化研讨会期间作为一个小组会面，并于 2018 年 3 月 15 日至 16 日在麻省理工学院举行的第二次研讨会期间再次会面。来自世界各地的研究人员代表了政府、工业界和学术界。世界上有几个研究小组已经为应用程序和通用用途提供了通用同态加密库。一些示例包括 [SEAL]、[HElib]、[PALISADE]、[cuHE]、[cuFHE]、[NFLlib]、[HEAAN] 和 [TFHE]。大多数用于同态加密的通用库都实现了基于环形错误学习 （RLWE） 问题的方案，其中许多库显示了基础环、错误分布和其他参数的通用选择。

Homomorphic Encryption is a breakthrough new technology which can enable private cloud storage and computation solutions, and many applications were described in the literature in the last few years. But before Homomorphic Encryption can be adopted in medical, health, and financial sectors to protect data and patient and consumer privacy, it will have to be standardized, most likely by multiple standardization bodies and government agencies. An important part of standardization is broad agreement on security levels for varying parameter sets. Although extensive research and benchmarking has been done in the research community to establish the foundations for this effort, it is hard to find all the information in one place, along with concrete parameter recommendations for applications and deployment.
同态加密是一项突破性的新技术，可以实现私有云存储和计算解决方案，并且在过去几年的文献中描述了许多应用。但是，在医疗、卫生和金融领域采用同态加密来保护数据以及患者和消费者隐私之前，它必须被标准化，最有可能是由多个标准化机构和政府机构标准化的。标准化的一个重要部分是就不同参数集的安全级别达成广泛共识。尽管研究界已经进行了广泛的研究和基准测试，为这项工作奠定了基础，但很难在一个地方找到所有信息，以及应用程序和部署的具体参数建议。

This document is an attempt to capture (at least part of) the collective knowledge regarding the currently known state of security of these schemes, to specify the schemes, and to recommend a wide selection of parameters to be used for homomorphic encryption at various security levels. We describe known attacks and their estimated running times in order to make these parameter recommendations.We also describe additional features of these encryption schemes which make them useful in different applications and scenarios.
本文档试图捕获（至少部分）有关这些方案当前已知安全状态的集体知识，指定方案，并推荐用于各种安全级别同态加密的广泛参数选择。我们描述了已知的攻击及其估计的运行时间，以便提出这些参数建议。我们还介绍了这些加密方案的其他功能，这些功能使它们在不同的应用程序和场景中很有用。


## Outline of the document: 
HES Section 1.1 standardizes the encryption schemes to be used. Section 1.1 consists of:
- Section 1.1.1: introduces notation and definitions.
- Section 1.1.2: defines the security properties for homomorphic encryption.
- Section 1.1.3: describes the BGV and BFV schemes.
- Section 1.1.4: described the GSW scheme.
- Section 1.1.5: mentions some alternative schemes: [YASHE13], [HPS98]/[LTV12], and [CKKS17].
- Section 1.1.6: describes additional features of the schemes.

HES Section 2.1 recommends parameter choices to achieve security. Section 2.1 consists of:
- Section 2.1.1: describes the hard problems: the LWE and RLWE assumptions.
- Section 2.1.2: describes known lattice attacks and their estimated running times.
- Section 2.1.3: mentioned the Arora-Ge attack on LWE.
- Section 2.1.4: discusses algebraic attacks on RLWE.
- Section 2.1.5: recommends concrete parameters to achieve various security levels.


It is expected that future work to update and expand this Homomorphic Encryption Standard will use the following numbering convention: 
- updates to the encryption schemes or additional schemes may be added as Sections 1.2, 1.3, … 
- updates to security levels or recommended parameters may be added as Sections 2.2, 2.3, … 
- a new section to cover API design is planned to be added as Section 3.0, and updated as 3.1, …
- a new section to cover applications may be added as Section 4.0, and updated as 4.1, …

In the appendix we list some aspects that are not specified in this document and are expected to be covered by future documents.

## Homomorphic Encryption Standard Section 1.1 Recommended Encryption Schemes

### Section 1.1.1 Notation and Definitions
#### ParamGen(λ, PT, K, B) → Params

The parameter generation algorithm is used to instantiate various parameters used in the HE algorithms outlined below. As input, it takes: 
- 𝜆 denotes the desired security level of the scheme. For instance, 128-bit security (𝜆 = 128) or 256-bit security. 表示方案所需的安全级别。例如，128 位安全性 （λ = 128） 或 256 位安全性。
- PT denotes the underlying plaintext space. Currently this standard specifies two types of parametrized plaintext spaces: modular integers (MI), and extension fields/rings (EX). We expect future versions of this document to introduce a third type of approximate numbers (AN). 表示基础明文空间。目前，该标准规定了两种类型的参数化明文空间：模块化整数 （MI） 和扩展场/环 （EX）。我们预计本文档的未来版本将引入第三种类型的近似数 （AN）
  - (MI) Modular integers are parametrized by the modulus p of the plaintext numbers to be encrypted, namely the plaintext space is $Z_p$. For instance, the parameter p=1024 means that the plaintext space is $Z_{1024}$ ,i.e., each individual element of the message space is an integer from the range [0, 1023] and all operations on individual elements are performed modulo p. 
  模整数由待加密的明文数的模数p参数化，即明文空间为$Z_p$。例如，参数 p=1024 表示明文空间为 $Z_{1024}$，即消息空间的每个单独元素都是 [0， 1023] 范围内的一个整数，并且对单个元素的所有操作都是模 p。
  - (EX) Extension rings/fields are parameterized by a modulus p as above, and in addition by a polynomial f(x) over Zp, specifying the plaintext space as $Z[x]/(p, f(x))$. Namely, each element of the message space is an integer polynomial of degree smaller than f(x) with coefficients from the range (0, p-1), and all operations over individual elements are performed modulo f(x), and modulo p. 
  如上所述，扩展环/场由模数 p 参数化，此外还通过 Zp 上的多项式 f（x） 参数化，将明文空间指定为 $Z[x]/(p, f(x))$。也就是说，消息空间的每个元素都是一个小于 f（x） 的整数多项式，系数范围为 （0， p-1），并且对单个元素的所有操作都执行模 f（x） 和模 p。
- 𝐾 denotes the dimension of the vectors to be encrypted. For instance, 𝐾 = 100, 𝑃𝑇 = (𝑀𝐼, 1024) means the messages to be encrypted are vectors $(𝑉_1, … , 𝑉_𝐾)$ where each 𝑉𝑖 is chosen from the range (0, 1023) and operations are performed component-wise. That is, by defintion, $(𝑉_1, … , 𝑉_𝐾) + (𝑉_1^′, … , 𝑉_𝐾^′ ) = (𝑉_1 + 𝑉_1^′, … , 𝑉_𝐾 + 𝑉_𝐾^′)$. The multiplication operation over two vectors is defined similarly. The space of all possible vectors $(𝑉_1, … , 𝑉_𝐾)$ is referred to as the message space (MS). 
表示要加密的向量的维度。例如，K = 100， PT = （MI， 1024） 表示要加密的消息是向量 $(𝑉_1, … , 𝑉_𝐾)$，其中每个 Vi 都是从范围 （0， 1023） 中选择的，并且按组件执行操作。也就是说，根据定义，$(𝑉_1, … , 𝑉_𝐾) + (𝑉_1^′, … , 𝑉_𝐾^′ ) = (𝑉_1 + 𝑉_1^′, … , 𝑉_𝐾 + 𝑉_𝐾^′)$。两个向量的乘法运算定义类似。所有可能的向量$(𝑉_1, … , 𝑉_𝐾)$的空间称为消息空间（MS）。
- 𝐵: denotes an auxiliary parameter that is used to control the complexity of the programs/circuits that one can expect to run over the encrypted messages. Lower parametersdenote “smaller”, or less expressive, or less complex programs/circuits. Lower parameters generally mean smaller parameters of the entire scheme. This, as a result, translates into smaller ciphertexts and more efficient evaluation procedures. Higher parameters generally increase key sizes, ciphertext sizes, and complexity of the evaluation procedures. Higher parameters are, of course, necessary to evaluate more complex programs. 
表示一个辅助参数，用于控制可以预期在加密消息上运行的程序/电路的复杂性。较低的参数表示“smaller”，或表现力较差，或程序/电路不太复杂。参数越低，通常意味着整个方案的参数越小。因此，这转化为更小的密文和更有效的评估程序。参数越高，通常会增加密钥大小、密文大小和评估过程的复杂性。当然，更高的参数对于评估更复杂的程序是必要的。


#### PubKeygen(Params) → SK, PK, EK

The public key-generation algorithm is used to generate a pair of secret and public keys. The public key can be shared and used by anyone to encrypt messages. The secret key should be kept private by a user and can be used to decrypt messages. The algorithm also generates an evaluation key that is needed to perform homomorphic operations over the ciphertexts. It should be given to any entity that will perform homomorphic operations over the ciphertexts. Any entity that has only the public and the evaluation keys cannot learn anything about the messages from the ciphertexts only. 
公钥生成算法用于生成一对密钥和公钥。任何人都可以共享和使用公钥来加密消息。密钥应由用户保密，并可用于解密消息。该算法还生成一个评估密钥，该密钥需要对密文执行同态操作。它应该提供给任何将对密文执行同态操作的实体。任何只有公共密钥和评估密钥的实体都无法仅从密文中了解消息的任何信息。


#### SecKeygen(Params) → SK, EK 

The secret key-generation algorithm is used to generate a secret key. This secret key is needed to both encrypt and decrypt messages by the scheme. It should be kept private by the user. The algorithm also generates an evaluation key that is needed to perform homomorphic operations over the ciphertexts. The evaluation key should be given to any entity that will perform homomorphic operations over the ciphertexts. Any entity that has only the evaluation key cannot learn anything about the messages from the ciphertexts only. 
密钥生成算法用于生成密钥。需要此密钥来加密和解密方案的消息。它应该由用户保密。该算法还生成一个评估密钥，该密钥需要对密文执行同态操作。应将评估密钥提供给将对密文执行同态操作的任何实体。任何只有评估密钥的实体都无法仅从密文中获知有关消息的任何信息。


#### PubEncrypt(PK, M) → C
The public encryption algorithm takes as input the public key of the scheme and any message M from the message space. The algorithm outputs a ciphertext C. This algorithm generally needs to be randomized (that is, use random or pseudo-random coins) to satisfy the security properties. 
公共加密算法将方案的公钥和来自消息空间的任何消息 M 作为输入。该算法输出密文 C。该算法一般需要随机化（即使用随机或伪随机币）来满足安全属性。

#### SecEncrypt(SK, M) → C
The secret encryption algorithm takes as input the secret key of the scheme and any message M from the message space. The algorithm outputs a ciphertext C. This algorithm generally needs to be randomized (that is, use random or pseudo-random coins) to satisfy the security properties. 
密钥加密算法将方案的密钥和来自消息空间的任何消息 M 作为输入。该算法输出密文 C。该算法一般需要随机化（即使用随机或伪随机币）来满足安全属性。

#### Decrypt(SK, C) → M
The decryption algorithm takes as input the secret key of the scheme, SK, and a ciphertext C. It outputs a message M from the message space. The algorithm may also output special symbol FAIL, if the decryption cannot successfully recover the encrypted message M. 
解密算法将方案的密钥 SK 和密文 C 作为输入。它从消息空间输出消息 M。如果解密不能成功恢复加密消息M，则该算法还可以输出特殊符号FAIL。


#### EvalAdd(Params, EK, C1, C2) → C3. 
EvalAdd is a randomized algorithm that takes as input the system parameters Params, the evaluation key EK, two ciphertexts C1 and C2, and outputs a ciphertext C3. 
EvalAdd 是一种随机算法，它以系统参数 Params、评估密钥 EK、两个密文 C1 和 C2 作为输入，并输出密文 C3。

The correctness property of EvalAdd is that if C1 is an encryption of plaintext element M1 and C2 is an encryption of plaintext element M2, then C3 should be an encryption of M1+M2.
EvalAdd 的正确性属性是，如果 C1 是明文元素 M1 的加密，而 C2 是明文元素 M2 的加密，那么 C3 应该是 M1+M2 的加密。


#### EvalAddConst(Params, EK, C1, M2) → C3.
EvalAddConst is a randomized algorithm that takes as input the system parameters Params, the evaluation key EK, a ciphertext C1, and a plaintext M2, and outputs a ciphertext C3.
EvalAddConst 是一种随机算法，它将系统参数 Params、评估密钥 EK、密文 C1 和明文 M2 作为输入，并输出密文 C3。

The correctness property of EvalAddConst is that if C1 is an encryption of plaintext element M1, then C3 should be an encryption of M1+M2.
EvalAddConst 的正确性属性是，如果 C1 是明文元素 M1 的加密，则 C3应该是 M1+M2 的加密。


#### EvalMult(Params, EK, C1, C2) → C3. 
EvalMult is a randomized algorithm that takes as input the system parameters Params, the evaluation key EK, two ciphertexts C1 and C2, and outputs a ciphertext C3. 
EvalMult 是一种随机算法，它以系统参数 Params、评估密钥 EK、两个密文 C1 和 C2 作为输入，并输出密文 C3。

The correctness property of EvalMult is that if C1 is an encryption of plaintext element M1 and C2 is an encryption of plaintext element M2, then C3 should be an encryption of M1*M2.
EvalMult 的正确性属性是，如果 C1 是明文元素 M1 的加密，而 C2 是明文元素 M2 的加密，那么 C3 应该是 M1*M2 的加密。


#### EvalMultConst(Params, EK, C1, M2) → C3.
EvalMultConst is a randomized algorithm that takes as input the system parameters Params, the evaluation key EK, a ciphertexts C1, and a plaintext M2, and outputs a ciphertext C3. 
EvalMultConst 是一种随机算法，它以系统参数 Params、评估密钥 EK、密文 C1 和明文 M2 作为输入，并输出密文 C3。

The correctness property of EvalMultConst is that if C1 is an encryption of plaintext element M1, then C3 should be an encryption of M1*M2.
EvalMultConst 的正确性属性是，如果 C1 是明文元素 M1 的加密，那么 C3 应该是 M1*M2 的加密。


#### Refresh(Params, flag, EK, C1) → C2.
Refresh is a randomized algorithm that takes as input the system parameters Params, a multi-valued flag (which can be either one of “Relinearize”, “ModSwitch” or “Bootstrap”), the evaluation key EK, and a ciphertext C1, and outputs a ciphertext C2. 
刷新是一种随机算法，它采用系统参数 Params、多值标志（可以是“Relinearize”、“ModSwitch”或“Bootstrap”之一）、评估密钥 EK 和密文 C1 作为输入，并输出密文 C2。

The correctness property of Refresh is that if C1 is an encryption of plaintext element M1, then C2 should be an encryption of M1 as well.
Refresh 的正确性属性是，如果 C1 是明文元素 M1 的加密，那么 C2 也应该是 M1 的加密。

The desired property of the Refresh algorithm is that it turns a “complex” ciphertext of a message into a “simple” one encrypting the same message. Two embodiments of the Refresh algorithm are (a) the bootstrapping procedure, which takes a ciphertext with large noise and outputs a ciphertext of the same message with a fixed amount of noise; and (b) the key-switching procedure, which takes a ciphertext under one key and outputs a ciphertext of the same message under a different key.
Refresh 算法的预期属性是它将消息的“复杂”密文转换为加密同一消息的“简单”密文。Refresh算法的两个实施例是：（a）引导过程，它采用具有较大噪声的密文，并输出具有固定噪声量的同一消息的密文;（b）密钥切换程序，即在一个密钥下获取密文，并在另一个密钥下输出同一消息的密文。


#### ValidityCheck(Params, EK, [C], COMP) → flag. 
ValidityCheck is an algorithm that takes as input the system parameters Params, the evaluation key EK, an array of ciphertexts [C], and a specification of the homomorphic computation encoded as a straight-line program COMP, and outputs a Boolean flag. 
ValidityCheck 是一种算法，它将系统参数 Params、评估密钥 EK、密文数组 [C] 和编码为直线程序 COMP 的同态计算规范作为输入，并输出布尔标志。

The correctness property of ValidityCheck is that if ValidityCheck outputs flag = 1, then doing the homomorphic computation COMP on the vector of ciphertexts [C] produces a ciphertext that decrypts to the correct answer.
ValidityCheck 的正确性属性是，如果 ValidityCheck 输出 flag = 1，则对密文向量 [C] 执行同态计算 COMP 会生成一个解密到正确答案的密文。


### Section 1.1.2 Properties

**Semantic Security or IND-CPA Security**: At a high level, a homomorphic encryption scheme is said to be secure if no adversary has an advantage in guessing (with better than 50% chance) whether a given ciphertext is an encryption of either one of two equally likely distinct messages. This requires encryption to be randomized so that two different encryptions of the same message do not look the same. 
**语义安全或 IND-CPA 安全**：在高层次上，如果没有对手在猜测给定密文是否是两个同样可能的不同消息中的任何一个的加密方面具有优势（有超过 50% 的机会），则称同态加密方案是安全的。这需要对加密进行随机化，以便同一消息的两种不同加密看起来不相同。

Suppose a user runs the parameter and the key-generation algorithms to provide the key tuple. An adversary is assumed to have the parameters, the evaluation key EK, a public key PK (only in the public￾key scheme) and can obtain encryptions of messages of its choice. The adversary is then given an encryption of one of two messages of its choice, computed by the above encryption algorithm, without knowing which message the encryption corresponds to. The security of HE then guarantees that the adversary cannot guess which message the encryption corresponds to with significant advantage better than a 50% chance. This captures the fact that no information about the messages is revealed in the ciphertext. 
假设用户运行参数和密钥生成算法来提供密钥元组。假设攻击者具有参数、评估密钥 EK、公钥 PK（仅在公钥方案中），并且可以获取其选择的消息加密。然后，攻击者将获得其选择的两条消息之一的加密，该加密由上述加密算法计算，而不知道加密对应于哪条消息。然后，HE 的安全性保证了对手无法猜测加密对应于哪条消息，并且具有优于 50% 的机会的显着优势。这捕获了这样一个事实，即密文中没有透露有关消息的信息。

**Compactness**: The compactness property of a homomorphic encryption scheme guarantees that homomorphic operations on the ciphertexts do not expand the length of the ciphertexts. That is, any evaluator can perform an arbitrary supported list of evaluation function calls and obtain a ciphertext in the ciphertext space (that does not depend on the complexity of the evaluated functions). 
**紧凑性**：同态加密方案的紧凑性保证了对密文的同态操作不会扩大密文的长度。也就是说，任何计算器都可以执行任意支持的评估函数调用列表，并在密文空间中获取密文（这不依赖于被评估函数的复杂性）。

**Efficient decryption**: Efficient decryption property says that the homomorphic encryption scheme always guarantees that the decryption runtime does not depend on the functions which was evaluated on the ciphertexts. 
**高效解密**：高效解密属性表示同态加密方案始终保证解密运行时不依赖于在密文上计算的函数。


### Section 1.1.3. The BGV and BFV Homomorphic Encryption Schemes 
In this section, we describe the two primary schemes for implementation of homomorphic encryption, [BGV12] and [B12]/[FV12], these two schemes are very similar. In Section 1.1.4. below we describe the GSW scheme, which is somewhat different. In Section 1.1.5, we also mention some alternative schemes [YASHE13], [HPS98]/[LTV12], and [CKKS17], but they are not described in this standard.
在本节中，我们将介绍实现同态加密的两种主要方案，[BGV12] 和 [B12]/[FV12]，这两种方案非常相似。在第 1.1.4 节中。下面我们描述GSW方案，它有些不同。在第 1.1.5 节中，我们还提到了一些替代方案 [YASHE13]、[HPS98]/[LTV12] 和 [CKKS17]，但本标准中没有描述它们。


#### a. Brakerski-Gentry-Vaikuntanathan (BGV)

We focus here on describing the basic version of the BGV encryption scheme. Optimizations to the basic scheme will be discussed at the end of this section.

##### BGV.ParamGen(λ, PT, K, B) → Params.

Recall that λ is the security level parameter, for BGV the plaintext space PT is either of type MI or EX with integer modulus p > 1, and K ≥ 1 is an integer vector length. 
回想一下，λ 是安全级别参数，对于 BGV，明文空间 PT 是 MI 或 EX 类型，整数模数 p > 1，K ≥ 1 是整数向量长度。

In the basic BGV scheme, the auxiliary input 𝐵 is an integer that determines the maximum multiplicative depth of the homomorphic computation. This is simply the maximum number of sequential multiplications required to perform the computation. For example, the function $𝑔(𝑥_1, 𝑥_2 , 𝑥_3, 𝑥_4) = 𝑥_1𝑥_2 + 𝑥_3𝑥_4$ has multiplicative depth 1.
在基本的BGV方案中，辅助输入B是一个整数，它决定了同态计算的最大乘法深度。这只是执行计算所需的最大顺序乘法数。例如，函数$𝑔(𝑥_1, 𝑥_2 , 𝑥_3, 𝑥_4) = 𝑥_1𝑥_2 + 𝑥_3𝑥_4$的乘法深度为 1。

In the basic BGV scheme, the parameters param include the ciphertext modulus parameter 𝑞 and a ring 𝑅 = 𝑍[𝑥]/𝑓(𝑥) and corresponding plaintext ring 𝑅/𝑝𝑅 and ciphertext ring 𝑅/𝑞𝑅. The parameters param also specify a “key distribution” 𝐷1 and an “error distribution” 𝐷2 over 𝑅, the latter is based on a Gaussian distribution with standard deviation σ set according to the security guidelines specified in Section 2.1.5. 
在基本的BGV方案中，参数参数包括密文模参数q和一个环 𝑅 = 𝑍[𝑥]/𝑓(𝑥) 和对应的明文环R/pR和密文环R/qR。参数参数还指定了 R 上的“密钥分布”D1 和“错误分布”D2，后者基于高斯分布，σ根据第 2.1.5 节中指定的安全准则设置标准差。


##### BGV.SecKeygen(params) → SK, EK 
In the basic BGV scheme, the secret key 𝑆𝐾 is an element 𝑠 in the ring 𝑅, chosen from distribution 𝐷1.

In the basic BGV scheme, there is no evaluation key EK.


##### BGV.PubKeygen(params) → SK, PK, EK.
In the basic BGV scheme, PubKeygen first runs SecKeygen and obtains (𝑆𝐾, 𝐸𝐾) where 𝑆𝐾 is an element 𝑠 that belongs to the ring 𝑅.

PubKeygen chooses a uniformly random element a from the ring 𝑅/𝑞𝑅 and outputs the public key 𝑃𝐾 which is a pair of ring elements $(𝑝𝑘_0, 𝑝𝑘_1) = (−𝑎, 𝑎𝑠 + 𝑝𝑒)$ where 𝑒 is chosen from the error distribution $𝐷_2$. 
PubKeygen 从环 R/qR 中选择一个均匀随机的元素 a，并输出公钥 PK，它是一对环元素 $(𝑝𝑘_0, 𝑝𝑘_1) = (−𝑎, 𝑎𝑠 + 𝑝𝑒)$，其中 𝑒 是从错误分布$𝐷_2$中选择的。


##### BGV.SecEncrypt(SK, M) → C
In the basic BGV scheme, SecEncrypt first maps the message 𝑀 which comes from the plaintext space (either $Z_p^r$ or $(Z_p[x]/f(x)^r)$ into an element $\hat𝑀$ of the ring 𝑅/𝑝𝑅.

SecEncrypt then samples a uniformly random element 𝑎 from the ring 𝑅/𝑞𝑅 and outputs the pair of ring elements $(𝑐_0, 𝑐_1) = (−𝑎, 𝑎𝑠 + 𝑝𝑒 + \hat𝑀)$ where 𝑒 is chosen from the error distribution $𝐷_2$. (See Comments 1, 2 below for more general methods of encoding the message during encryption. The same comments apply also to public-key encryption with BGV.)
然后，SecEncrypt 从环 R/qR 中采样一个均匀随机的元素 a，并输出一对环元素$(𝑐_0, 𝑐_1) = (−𝑎, 𝑎𝑠 + 𝑝𝑒 + \hat𝑀)$，其中 𝑒 是从误差分布 $𝐷_2$ 中选择的。（请参阅下面的注释 1、2，了解在加密期间对消息进行编码的更一般方法。同样的注释也适用于使用 BGV 进行公钥加密。


##### BGV.PubEncrypt(PK, M) → C
In the basic BGV scheme, Pub.Encrypt first maps the message 𝑀 which comes from the plaintext space $𝑍_𝑝^𝑘$ into an element $\hat𝑀$ of the ring 𝑅/𝑝𝑅. Recall that the public key 𝑃𝐾 is a pair of elements $(𝑝𝑘_0, 𝑝𝑘_1)$.
在基本的 BGV 方案中，Pub.Encrypt 首先将来自明文空间$𝑍_𝑝^𝑘$的消息 M 映射到环 R/pR 的元素 $\hat𝑀$中。回想一下，公钥 PK 是一对元素 $(𝑝𝑘_0, 𝑝𝑘_1)$。

PubEncrypt then samples three elements 𝑢 from distribution $𝐷_1$ and $𝑒_1, 𝑒_2$ from the error distribution $𝐷_2$ and outputs the pair of ring elements $(𝑐_0, 𝑐_1) = (𝑝𝑘_0𝑢 + 𝑝𝑒_1, 𝑝𝑘_1𝑢 + 𝑝𝑒_2 + \hat𝑀)$. 


##### BGV.Decrypt(SK, C) → M

In the basic BGV scheme, Decrypt takes as input the secret key which is an element 𝑠 of the ring 𝑅, and a ciphertext $𝐶 = (𝑐_0, 𝑐_1)$ which is a pair of elements from the ring 𝑅/𝑞𝑅. 
在基本的 BGV 方案中，Decrypt 将密钥（环 R 的元素 s）和密文$𝐶 = (𝑐_0, 𝑐_1)$作为输入，密文是环 R/qR 中的一对元素。

We remark that a ciphertext 𝐶 produced as the output of the encryption algorithm has two elements in 𝑅/𝑞𝑅, but upon homomorphic evaluation, ciphertexts can grow to have more ring elements. The decryption algorithm can be modified appropriately to handle such ciphertexts.
我们指出，作为加密算法输出的密文 C 在 R/qR 中有两个元素，但在同态评估时，密文可以增长为具有更多的环元素。可以适当修改解密算法以处理此类密文。

Decrypt first computes the ring element $𝑐_0𝑠 + 𝑐_1$ over 𝑅/𝑞𝑅 and interprets it as an element 𝑐’ in the ring 𝑅. It then computes 𝑐’ (mod 𝑝), an element of 𝑅/𝑝𝑅, which it outputs.
Decrypt 首先计算环元素$𝑐_0𝑠 + 𝑐_1$ over R/qR，并将其解释为环 R 中的元素 𝑐’。然后，它计算 𝑐’ (mod 𝑝)，这是 R/pR 的一个元素，并输出该元素。


##### BGV.EvalAdd(Params, EK, C1, C2) → C3. 
In the basic BGV scheme, EvalAdd takes as input ciphertexts 𝐶1 = (𝑐1,0, 𝑐1,1) and 𝐶2 = (𝑐2,0, 𝑐2,1 ) and 
outputs 𝐶3 = (𝑐1,0 + 𝑐2,0, 𝑐1,1 + 𝑐2,1), where the operations are done in 𝑅/𝑞𝑅. 

##### BGV.EvalMult(Params, EK, C1, C2) → C3.
In the basic BGV scheme, EvalMult takes as input ciphertexts $𝐶1 = (𝑐_{1,0}, 𝑐_{1,1})$ and $𝐶2 = (𝑐_{2,0}, 𝑐_{2,1})$and outputs $𝐶3 = (𝑐_{1,0}𝑐_{2,0}, 𝑐_{1,0}𝑐_{2,1} + 𝑐_{1,1}𝑐_{2,0}, 𝑐_{1,1}𝑐_{2,1})$, where the operations are done in 𝑅/𝑞𝑅.


**Comment 1.** The noise term $𝑝𝑒 + \hat𝑀$ in the encryption procedure can be generalized to an error term drawn from the coset $\hat𝑀 + 𝑝𝑅$, according to an error-sampling procedure. All the considerations discussed below for the error distribution $𝐷_2$, apply equally to the error-sampling procedure in this more general implementation.
根据错误采样过程，加密过程中的噪声项 $𝑝𝑒 + \hat𝑀$ 可以推广为从 coset $\hat𝑀 + 𝑝𝑅$ 中提取的错误项。下面讨论的关于误差分布$𝐷_2$的所有注意事项，同样适用于此更通用的实现中的错误采样过程。

**Comment 2.** There is also an equivalent “MSB encoding” of the message for BGV encryption, where the message is encoded as $𝑊\hat𝑀+e$ (with 𝑊 = ⌊𝑞/𝑝⌋, similarly to the BFV scheme below). There are lossless conversions between these two encoding methods, as long as the plaintext modulus p is co-prime with the ciphertext modulus q.
对于 BGV 加密，消息还有一个等效的“MSB 编码”，其中消息被编码为 $𝑊\hat𝑀+e$（W = ⌊q/p⌋，类似于下面的 BFV 方案）。这两种编码方法之间存在无损转换，只要明文模量 p 与密文模量 q 共质即可。


##### The Full BGV Scheme
In the basic BGV scheme, ciphertexts grow as a result of EvalMult. For example, given two ciphertexts each composed of two ring elements, EvalMult as described above results in three ring elements. This can be further repeated, but has the disadvantage that upon evaluating a degree-𝑑 polynomial on the plaintexts, the resulting ciphertext has 𝑑 + 1 ring elements.
在基本的 BGV 方案中，密文因 EvalMult 而增长。例如，给定两个密文，每个密文由两个环形元素组成，如上所述，EvalMult 会产生三个环形元素。这可以进一步重复，但缺点是，在计算明文上的 d 次多项式时，生成的密文具有 d + 1 个环元素。

This deficiency is mitigated in the full BGV scheme, with two additional procedures. The first is called “Key Switching” or “Relinearization” which is implemented by calling the Refresh subroutine with flag = “KeySwitch”, and the second is “Modulus Switching” or “Modulus Reduction” which is implemented by calling the Refresh subroutine with flag = “ModSwitch”. Support for key switching and modulus switching also necessitates augmenting the key generation algorithm.
在完整的BGV方案中，通过两个额外的程序，这一缺陷得到了缓解。第一个称为“密钥切换”或“Relinearization”，它是通过调用带有 flag = “KeySwitch” 的 Refresh 子程序来实现的，第二个是“模数切换”或“模数降低”，它是通过调用带有 flag = “ModSwitch” 的 Refresh 子程序来实现的。对密钥切换和模数切换的支持还需要增强密钥生成算法。

For details on the implementation of the full BGV scheme, we refer the reader to [BGV12].

**Properties Supported.** The BGV scheme supports many features described in Section 6, including packed evaluations of circuits and can be extended into a threshold homomorphic encryption scheme. In terms of security, the BGV homomorphic evaluation algorithms can be augmented to provide evaluation privacy (with respect to semi-honest adversaries).
**支持的属性。 BGV 方案支持第 6 节中描述的许多功能，包括电路的打包评估，并且可以扩展为阈值同态加密方案。在安全性方面，BGV同态评估算法可以得到增强，以提供评估隐私（相对于半诚实的对手）。


#### b. Brakerski/Fan-Vercauteren (BFV)
We follow the same notations as the previous section. 

##### BFV.ParamGen(λ, PT, K, B) → Params.
We assume the parameters are instantiated following the recommendations outlined in Section 5. Similarly to BGV, the parameters include:
- Key- and error-distributions $𝐷_1,𝐷_2$ 
- a ring 𝑅 and its corresponding integer modulus 𝑞 
- Integer modulus 𝑝 for the plaintext
In addition, the BFV parameters also include:
- Integer 𝑇, and $𝐿 = log_𝑇 𝑞$. T is the bit-decomposition modulus. T是位分解模量。
- Integer 𝑊 = ⌊𝑞/𝑝⌋ 

##### BFV.SecKeygen(Params) -> SK, EK
The secret key 𝑆𝐾 of the encryption scheme is a random element𝑠 from the distribution $𝐷_1$ defined as per Section 5. The evaluation key consists of 𝐿 LWE samples encoding the secret 𝑠 in a specific fashion. In particular, for 𝑖 = 1, … , 𝐿, sample a random $𝑎_𝑖$ from 𝑅/𝑞𝑅 and error $𝑒_𝑖$ from $𝐷_2$, compute
加密方案的密钥 SK 是来自第 5 节定义的分布 $𝐷_1$ 的随机元素。评估密钥由 L LWE 样本组成，这些样本以特定方式对密钥进行编码。特别是，对于 i = 1， ... ， L，从 R/qR 中抽取随机 $𝑎_𝑖$，从$𝐷_2$中抽取误差 $𝑒_𝑖$ ，计算

$$𝐸𝐾_𝑖 = (−(𝑎_𝑖𝑠 + 𝑒_𝑖) + 𝑇^𝑖𝑠^2, 𝑎_𝑖)$$

and set $𝐸𝐾 = (𝐸𝐾_1, … , 𝐸𝐾_𝐿)$. 


##### BFV.PubKeygen(params) -> SK, PK, EK.
The secret key SK of the encryption scheme is a random element 𝑠 from the distribution 𝐷1. The public key is a random LWE sample with the secret 𝑠. In particular, it is computed by sampling a random element 𝑎 from 𝑅/𝑞𝑅 and an error 𝑒 from the distribution $𝐷_2$ and setting: 
加密方案的密钥 SK 是分布 D1 中的随机元素 s。公钥是带有密钥 s 的随机 LWE 样本。具体而言，它是通过从 R/qR 中抽取随机元素 a 和从分布 D2 中抽取误差 e 来计算的，并设置：

𝑃𝐾 = (−(𝑎𝑠 + 𝑒), 𝑎), where all operations are performed over the ring 𝑅/𝑞𝑅. 

The evaluation key is computed as in BFV.SecKeygen. 评估密钥的计算方式与BFV.SecKeygen相同。


##### BFV.PubEncrypt(PK, M) -> C
BFV.Pub.Encrypt first maps the message 𝑀 which comes from the message space into an element in the ring 𝑅/𝑝𝑅 . 

To encrypt a message 𝑀 from 𝑅/𝑝𝑅, parse the public key as a pair $(𝑝𝑘_0, 𝑝𝑘_1)$. Encryption consists of two LWE samples using a secret 𝑢 where $(𝑝𝑘_0, 𝑝𝑘_1)$ is treated as public randomness. The first LWE sample encodes the message 𝑀, whereas the second sample is auxiliary. 
要加密来自 R/pR 的消息 M，请将公钥解析为一对$(𝑝𝑘_0, 𝑝𝑘_1)$。加密由两个使用密钥 u 的 LWE 样本组成，其中$(𝑝𝑘_0, 𝑝𝑘_1)$被视为公共随机性。第一个 LWE 样本对消息 M 进行编码，而第二个样本是辅助样本。

In particular, $𝐶 = (𝑝𝑘_0𝑢 + 𝑒_1 + 𝑊𝑀, 𝑝𝑘_1𝑢 + 𝑒_2)$ where 𝑢 is a sampled from 𝐷1 and 𝑒1, 𝑒2 are sampled from 𝐷2. 

##### BFV.SecEncrypt(PK, M) -> C

##### BFV.Decrypt(SK, C) -> M
The main invariant of the BFV scheme is that when we interpret the elements of a ciphertext 𝐶 as the coefficients of a polynomial then, 𝐶(𝑠) = 𝑊 𝑀 + 𝑒 for some “small” error 𝑒. The message 𝑀 can be recovered by dividing the polynomial 𝐶(𝑠) by 𝑊 , rounding each coefficient to the nearest integer, and reducing each coefficient modulo 𝑝. 
BFV 方案的主要不变量是，当我们将密文 C 的元素解释为多项式的系数时，对于一些“小”误差 e，C（s） = W M + e。消息 M 可以通过将多项式 C（s） 除以 W 来恢复，将每个系数四舍五入到最接近的整数，并减去每个系数模 p。


##### BFV.EvalAdd(EK, C1, C2) -> C3
Parse the ciphertexts as $𝐶𝑖 = (𝑐_{𝑖,0}, 𝑐_{𝑖,1})$. Then, addition corresponds to component-wise addition of two ciphertext components. That is, $𝐶3 = (𝑐_{1,0} + 𝑐_{2,0}, 𝑐_{1,1} + 𝑐_{2,1})$.
将密文解析为$𝐶𝑖 = (𝑐_{𝑖,0}, 𝑐_{𝑖,1})$。然后，加法对应于两个密文组件的组件相加。即，$𝐶3 = (𝑐_{1,0} + 𝑐_{2,0}, 𝑐_{1,1} + 𝑐_{2,1})$。

It is easy to verify that $𝐶3(𝑠) = 𝑊 (𝑀_1 + 𝑀_2) + 𝑒$, where 𝑀1, 𝑀2 are messages encrypted in 𝐶1, 𝐶2 and 𝑒 is the new error component. 
很容易验证$𝐶3(𝑠) = 𝑊 (𝑀_1 + 𝑀_2) + 𝑒$，其中 M1、M2 是在 C1 中加密的消息，C2 和 e 是新的错误组件。


##### BFV.EvalMult(EK, C1, C2) -> C3
EvalMult takes as input ciphertexts $𝐶1 = (𝑐_{1,0}, 𝑐_{1,1})$ and $𝐶2 = (𝑐_{2,0}, 𝑐_{2,1})$. First, it computes 𝐶3′ = $(𝑐_{1,0}𝑐_{2,0}, 𝑐_{1,0}𝑐_{2,1} + 𝑐_{1,1}𝑐_{2,0}, 𝑐_{1,1}𝑐_{2,1})$ over the integers (instead of mod 𝑞 as in BGV scheme above). Then set $𝐶3 = 𝑟𝑜𝑢𝑛𝑑((\frac𝑝𝑞) 𝐶3^′) 𝑚𝑜𝑑 𝑞$.

One can verify that 𝐶3(𝑠) = 𝑊(𝑀1 ∗ 𝑀2) + 𝑒, for some error term 𝑒. 

Note that the ciphertext size increases in this operation. One may apply a Relinearization algorithm as in the BGV scheme to obtain a new ciphertext of the original size encrypting the same message 𝑀1 ∗ 𝑀2. 
请注意，密文大小在此操作中会增加。可以应用 BGV 方案中的 Relinearization 算法来获取原始大小的新密文，对相同的消息 M1 ∗ M2 进行加密。

**Properties Supported.** The complete BFV scheme supports many features described in Section 6, including packed evaluations of circuits and can be extended into a threshold homomorphic encryption scheme. In terms of security, the BFV homomorphic evaluation algorithms can be augmented to provide evaluation privacy.
**支持的属性。 完整的 BFV 方案支持第 6 节中描述的许多功能，包括电路的打包评估，并且可以扩展为阈值同态加密方案。在安全性方面，BFV同态评估算法可以得到增强，以提供评估隐私。

For details on the implementation of the full BFV scheme, we refer the reader to [B12], [FV12]. 


#### c. Comparison between BGV and BFV
When implementing HE schemes, there are many choices which can be made to optimize performance for different architectures and different application scenarios. This makes a direct comparison of these schemes quite challenging. A paper by Costache and Smart [CS16] gives some initial comparisons between BGV, BFV and two of the schemes described below: YASHE and LTV/NTRU. A paper by Kim and Lauter [KL15] compares the performance of the BGV and YASHE schemes in the context of applications.Since there is further ongoing work in this area, we leave this comparison as an open research question.
在实施 HE 方案时，可以做出许多选择来优化不同架构和不同应用场景的性能。这使得对这些方案的直接比较非常具有挑战性。Costache 和 Smart [CS16] 的一篇论文对 BGV、BFV 和下面描述的两种方案进行了一些初步比较：YASHE 和 LTV/NTRU。Kim 和 Lauter [KL15] 的一篇论文比较了 BGV 和 YASHE 方案在应用环境中的性能。由于该领域还有进一步的工作，我们将这种比较作为一个开放的研究问题。



### Section 1.1.4. The GSW Scheme and bootstrapping
Currently, the most practical homomorphic encryption schemes only allow to perform bounded depth computations. These schemes can be transformed into fully homomorphic ones (capable of arbitrary computations) using a “bootstrapping” technique introduced by Gentry [G09], which essentially consists of a homomorphic evaluation of the decryption algorithm given the encryption of the secret key. Bootstrapping is a very time-consuming operation and improving on its efficiency is still a very active research area. So, it may still not be ready for standardization, but it is the next natural step to be considered. 
目前，最实用的同态加密方案只允许执行有界深度计算。这些方案可以使用 Gentry [G09] 引入的“引导”技术转换为完全同态的方案（能够进行任意计算），该技术本质上包括对给定密钥加密的解密算法的同态评估。引导是一项非常耗时的操作，提高其效率仍然是一个非常活跃的研究领域。因此，它可能还没有准备好进行标准化，但这是下一个自然而然的步骤。

Bootstrapping using the BGV or BFV schemes requires assuming that lattice problems are computationally hard to approximate within factors that grow superpolynomially in the lattice dimension n. This is a stronger assumption than the inapproximability within polynomial factors required by standard (non-homomorphic) lattice-based public key encryption.
使用 BGV 或 BFV 方案进行自举需要假设晶格问题在计算上难以近似在晶格维数 n 中超多项式增长的因子内。这比标准（非同态）基于格子的公钥加密所要求的多项式因子内的不近似性更强。

In [GSW13], Gentry, Sahai and Waters proposed a new homomorphic encryption scheme (still based on lattices) that offers a different set of trade-offs than BGV and BFV. An important feature of this scheme is that it can be used to bootstrap homomorphic encryption based on the assumption that lattice problems are hard to approximate within polynomial factors. Here we briefly describe the GSW encryption and show how both its security and applicability to bootstrapping are closely related to LWE encryption, as used by the BGV and BFV schemes. So, future standardization of bootstrapping (possibly based on the GSW scheme) could build on the current standardization effort.
在 [GSW13] 中，Gentry、Sahai 和 Waters 提出了一种新的同态加密方案（仍然基于格），它提供了与 BGV 和 BFV 不同的权衡。该方案的一个重要特征是，它可用于基于格问题在多项式因子内难以近似的假设来引导同态加密。在这里，我们简要介绍了 GSW 加密，并展示了其安全性和对引导的适用性如何与 BGV 和 BFV 方案使用的 LWE 加密密切相关。因此，未来的自举标准化（可能基于GSW方案）可以建立在当前的标准化工作之上。

For simplicity, we focus on secret key encryption, as this is typically enough for applications to bootstrapping. The GSW secret key encryption scheme (or, more specifically, its secret key, ring-based variant presented in [AP14, DM15]) can be described as follows:
为简单起见，我们专注于密钥加密，因为这通常足以让应用程序引导。GSW密钥加密方案（或者更具体地说，[AP14，DM15]中介绍的基于密钥的基于环的变体）可以描述如下：
- GSW.Keygen(params):
This is essentially the same as the key generation procedure of the BGV or BFV schemes, taking a similar set of security parameters, and producing a random ring element S which serves as a secret key.
这与 BGV 或 BFV 方案的密钥生成过程基本相同，采用一组类似的安全参数，并生成一个用作密钥的随机环元素 S。

- GSW.SecEncrypt(S,M):
Choose an uniformly random vector 𝐴 in 𝑅2 log(𝑞), a small random vector 𝐸 (with entries chosen independently at random from the error distribution), and output the ciphertext 𝐶 = (𝐴, 𝐴 ∗ 𝑆 + 𝐸) + 𝑀 ∗ 𝐺 where 𝐺 = [𝐼, 2 𝐼, … , 2𝑘−1𝐼] is a gadget matrix consisting of 𝑘 = 𝑙𝑜𝑔(𝑞) copies of the 2x2 identity matrix 𝐼 (over the ring), scaled by powers of 2.
在 R2 log（q） 中选择一个均匀随机的向量 A，一个小的随机向量 E（从误差分布中随机选择条目），并输出密文 C = （A， A ∗ S + E） + M ∗ G，其中 G = [I， 2 I， ...， ， 2k−1I] 是一个小工具矩阵，由 2x2 单位矩阵 I 的 k = log（q） 副本组成（在环上）， 按 2 的幂缩放。

We note that there are other possibilities for choosing the gadget matrix G above (for example the constants 2,4, … , 2𝑘−1can be replaced by others). Other choices may be described in future documents. 
我们注意到，选择上面的小工具矩阵 G 还有其他可能性（例如常数 2,4， ...， 2k−1 可以被其他常数替换）。其他选择可能会在以后的文件中描述。

We omit the description of the decryption procedure, as it is not needed for bootstrapping. Notice that:
我们省略了解密过程的描述，因为引导不需要它。请注意：
- The secret key generation process is the same as most other LWE-based encryption schemes, including BGV and BFV.
- The encryption procedure essentially consists of 2 𝑙𝑜𝑔(𝑞) independent application of the basic LWE/BGV/BFV encryption: choose random key elements 𝑎 and 𝑒, and outputs (𝑎, 𝑎𝑠 + 𝑒 + 𝑚), but applied to scaled copies of the message 𝑚 = 2𝑖 𝑀. (The even rows of the GSW ciphertext encrypt the message as (𝑎 + 𝑚, 𝑎𝑠 + 𝑒), but this is just a minor variant on LWE encryption, and equivalent to it from a security standpoint.)
加密过程实质上包括 2 个独立于 log（q） 的基本 LWE/BGV/BFV 加密应用：选择随机密钥元素 a 和 e，并输出 （a， as + e + m），但应用于消息 m = 2i M 的缩放副本。 （GSW 密文的偶数行将消息加密为 （a + m， as + e）， 但这只是 LWE 加密的一个小变体，从安全角度来看，它等效于它。

- Security rests on the standard LWE assumption, as used also by BGV and BFV, which says that the distribution (𝐴, 𝐴 ∗ 𝑆 + 𝐸) is pseudorandom. 
安全性基于标准的 LWE 假设，BGV 和 BFV 也使用这种假设，即分布（A、A ∗ S + E）是伪随机的。

So, GSW can be based on LWE security estimates similar to those used to instantiate the BGV or BFV cryptosystems. 因此，GSW可以基于LWE安全估计，类似于用于实例化BGV或BFV密码系统的估计。


In [GSW13] it is shown how (a public key version of) this cryptosystem supports both addition and multiplication, without the need for an evaluation key, which has applications to identity-based and attribute-based homomorphic encryption. Later, in [BV14] it was observed how the GSW multiplication operation exhibits an asymmetric noise growth that can be exploited to implement bootstrapping based on the hardness of approximating lattice problems within polynomial factors. Many subsequent papers (e.g., [AP14, DM15, GINX16, CGGI16]) improve on the efficiency of [BV14], but they all share the following features with [BV14]: 
在 [GSW13] 中，展示了该密码系统（公钥版本）如何支持加法和乘法，而无需评估密钥，该密钥具有基于身份和基于属性的同态加密的应用。后来，在 [BV14] 中观察到 GSW 乘法运算如何表现出不对称噪声增长，可以利用这种增长来实现基于多项式因子内近似晶格问题的硬度的自举。许多后续论文（例如，[AP14，DM15，GINX16，CGGI16]）提高了[BV14]的效率，但它们都共享[BV14] 的以下功能：
- They all use variants of the GSW encryption to implement bootstrapping.
它们都使用 GSW 加密的变体来实现引导。

- Security only relies on the hardness of approximating lattice problems within polynomial factors.安全性仅取决于多项式因子内近似晶格问题的硬度。

- They are capable of bootstrapping any LWE-based encryption scheme, i.e., any scheme which includes an LWE encryption of the message as part of the ciphertext. LWE-based schemes include BGV, BFV and GSW.
它们能够引导任何基于 LWE 的加密方案，即任何将消息的 LWE 加密作为密文的一部分的方案。基于 LWE 的方案包括 BGV、BFV 和 GSW。

In particular, GSW can be used to implement the bootstrapping procedure for BGV and BFV and turn them into fully homomorphic encryption (FHE) schemes.
特别是，GSW 可用于实现 BGV 和 BFV 的引导过程，并将它们转换为完全同态加密 （FHE） 方案。


### Section 1.1.5. Other Schemes
Yet Another Somewhat Homomorphic Encryption ([YASHE13]) is similar to the BGV and BFV schemes and offers the same set of features. 

The scheme NTRU/Lopez-Alt-Tromer-Vaikuntanathan ([HPS98]/[LTV12]) relies on the NTRU assumption (also called the “small polynomial ratios assumption”). It offers all the features of BGV and BFV, and in addition, also offers an extension that supports multi-key homomorphism. However, it must be used with a much wider error distribution than the other schemes that are described in this document (or else it becomes insecure), and therefore it should only be used with a great deal of care. This standard does not cover security for these schemes.
方案 NTRU/Lopez-Alt-Tromer-Vaikuntanathan （[HPS98]/[LTV12]） 依赖于 NTRU 假设（也称为“小多项式比率假设”）。它提供了 BGV 和 BFV 的所有功能，此外，还提供了支持多键同态的扩展。但是，与本文档中描述的其他方案相比，它必须具有更广泛的错误分布（否则会变得不安全），因此只能非常小心地使用它。本标准不包括这些方案的安全性。

Another scheme, called CKKS, with plaintext type approximate numbers, was recently proposed by Cheon, Kim, Kim and Song [CKKS17]. This scheme is not described here, but we expect future version of this standard to include it.
Cheon， Kim， Kim and Song [CKKS17] 最近提出了另一种称为 CKKS 的方案，具有明文类型的近似数字。此处未描述此方案，但我们希望该标准的未来版本将包含它。


### Section 1.1.6. Additional Features & Discussion

#### a. Distributed HE
Homomorphic Encryption is especially suitable to use for multiple users who may want to run computations on an aggregate of their sensitive data. For the setting of multiple users, an additional property which we call threshold-HE is desirable. In threshold-HE the key-generation algorithms, encryption and decryption algorithms are replaced by a distributed-key-generation (DKG) algorithm, distributed-encryption (DE) and distributed-decryption (DD) algorithms. Both the distributed-key￾generation algorithm and the distributed-decryption algorithm are executed via an interactive process among the participating users. The evaluation algorithms EvalAdd, EvalMult, EvalMultConst, EvalAddConst and Refresh remain unchanged.
同态加密特别适合于可能希望对其敏感数据的聚合运行计算的多个用户。对于多个用户的设置，我们称之为阈值 HE 的附加属性是可取的。在阈值 HE 中，密钥生成算法、加密和解密算法被分布式密钥生成 （DKG） 算法、分布式加密 （DE） 和分布式解密 （DD） 算法所取代。分布式密钥生成算法和分布式解密算法都是通过参与用户之间的交互过程执行的。评估算法 EvalAdd、EvalMult、EvalMultConst、EvalAddConst 和 Refresh 保持不变。

We will now describe the functionality of the new algorithms.

We begin with the distributed-key-generation (DKG) algorithm to be implemented by an interactive protocol among 𝑡 parties 𝑝1, … , 𝑝𝑡. The DKG algorithm is a randomized algorithm. The inputs to DKG are: security parameter, number of parties 𝑡, and threshold parameter 𝑑. The output of DKG is a vector of secret keys 𝑠 = (𝑠1, . . . . , 𝑠𝑡) of dimension 𝑡 and a public evaluation key Ek where party 𝑝𝑖 receives (Ek,𝑠𝑖). We remark that party 𝑝𝑖 doesn’t receive 𝑠𝑗 for 𝑖 ≠ 𝑗 and party 𝑖 should maintain the secrecy of its secret key 𝑠𝑖.
我们从分布式密钥生成 （DKG） 算法开始，该算法将由 t 方 p1， ... ， pt 之间的交互式协议实现。DKG算法是一种随机算法。DKG 的输入为：安全参数、参与方数 t 和阈值参数 d。DKG 的输出是维度 t 的密钥 s = （s1， . . . . ， st） 和公共评估密钥 Ek 的向量，其中 party pi 接收 （Ek，si）。我们指出，方 pi 不会收到 i ≠ j 的 sj，方 i 应该保持其密钥 si 的保密性。

Next, the distributed-encryption (DE) algorithm is described. The DE algorithm is a randomized algorithm which can be run by any party 𝑝𝑖. The inputs to DE run by party 𝑝𝑖 are: the secret key 𝑠𝑖 and the plaintext 𝑀. The output of DE is a ciphertext C
接下来，介绍分布式加密 （DE） 算法。DE 算法是一种随机算法，可以由任何一方 pi 运行。参与方 pi 运行的 DE 输入是：密钥 si 和明文 M。DE 的输出是密文 C

Finally, we describe the distributed-decryption (DD) algorithm to be implemented by an interactive protocol among a subset of the 𝑡 parties 𝑝1, … , 𝑝𝑡. The DD algorithm is a randomized algorithm. The inputs to DD are: a subset of secret keys 𝑠 = (𝑠1, . . . . , 𝑠𝑡), the threshold parameter 𝑑, and a ciphertext C. In particular, every participating party 𝑝𝑖 provides the input 𝑠𝑖. The ciphertext C can be provided by any party. The output of DD is: plaintext 𝑀.
最后，我们描述了分布式解密（DD）算法，该算法由交互协议在t方p1，...，pt的子集之间实现。DD算法是一种随机算法。DD 的输入是：密钥 s = （s1， . . . . ， st） 的子集、阈值参数 d 和密文 C。特别是，每个参与方 pi 都提供输入 si。密文 C 可以由任何一方提供。DD 的输出为：明文 M。

The correctness requirement that the above algorithms should satisfy is as follows. If at least 𝑑 of the parties correctly follow the prescribed interactive protocol that implements the DD decryption algorithm, then the output of the decryption algorithm will be correct.The security requirement is for semantic security to hold as long as fewer than 𝑑 parties collude adversarially.
上述算法应满足的正确性要求如下。如果至少有 d 方正确地遵循了实现 DD 解密算法的规定交互协议，则解密算法的输出将是正确的。安全要求是，只要少于 d 方进行对抗性串通，语义安全就成立。

An example usage application for (DKG,DE,DD) is for two hospitals, 𝑡 = 2 and 𝑑 = 2 with sensitive data sets 𝑀1 and 𝑀2(respectively) who want to compute some analytics 𝐹 on the joint data set without revealing anything about 𝑀1 and 𝑀2 except for what is revealed by 𝐹(𝑀1, 𝑀2).
（DKG，DE，DD） 的示例使用应用程序适用于两家医院，t = 2 和 d = 2，分别具有敏感数据集 M1 和 M2，他们希望在联合数据集上计算一些分析 F，而不透露任何关于 M1 和 M2 的信息，除了 F（M1， M2） 显示的内容。

In such a case the two hospitals execute the interactive protocol for DKG and obtain their respective secret keys 𝑠1 and 𝑠2 and the evaluation key EK. They each use DE on secret key 𝑠𝑖 and data 𝑀𝑖 to produce ciphertext Ci. The evaluation algorithms on C1, C2 and the evaluation key EK allow the computation of a ciphertext C which is an encryption of 𝐹(𝑀1, 𝑀2). Now, the hospitals execute the interactive protocol DD using their secret keys and ciphertext C to obtain 𝐹(𝑀1, 𝑀2).
在这种情况下，两家医院执行 DKG 的交互式协议，并获取各自的密钥 s1 和 s2 以及评估密钥 EK。它们各自使用密钥 si 上的 DE 和数据 Mi 来生成密文 Ci。C1、C2 和评估密钥 EK 上的评估算法允许计算密文 C，该密文是 F（M1， M2） 的加密。现在，医院使用其密钥和密文 C 执行交互式协议 DD 以获得 F（M1， M2）。


#### b. Active Attacks
One can consider stronger security requirements beyond semantic security. For example, consider an attack on a client that holds data 𝑀 and wishes to compute 𝐹(𝑀) for a specified algorithm 𝐹, and wants to outsource the computation of 𝐹(𝑀) to a cloud, while maintaining the privacy of 𝑀. The client encrypts 𝑀 into ciphertext C and hands C to the cloud server. The server is supposed to use the evaluation algorithms to compute a ciphertext C’ which is an encryption of 𝐹(𝑀) and return this to the client for decryption.
除了语义安全之外，还可以考虑更严格的安全要求。例如，考虑对持有数据 M 并希望计算指定算法 F 的 F（M） 的客户端的攻击，并希望将 F（M） 的计算外包给云，同时维护 M 的隐私。客户端将 M 加密为密文 C，并将 C 交给云服务器。服务器应该使用评估算法来计算密文 C'，它是 F（M） 的加密，并将其返回给客户端进行解密。

Suppose that instead the cloud computes some other C’’ which is the encryption of 𝐺(𝑀) for some other function 𝐺. This may be problematic to the client as it would introduce errors of potentially significant consequences. This is an example of an active attack which is not ruled out by semantic security. 
假设云计算了一些其他的 C''，这是其他一些函数 G 的 G（M） 加密。这对客户来说可能是有问题的，因为它会引入可能产生重大后果的错误。这是语义安全不排除的主动攻击示例。

Another, possibly even more severe attack, is the situation where the adversary somehow gains the ability to decrypt certain ciphertexts, or glean some information about their content (perhaps by watching the external behavior of the client after decrypting them). This may make it possible to the attacker to mount (perhaps limited) chosen-ciphertext attacks, which may make it possible to compromise the security of encrypted data. Such attacks are not addressed by the semantic security guarantee, countering them requires additional measures beyond the use of homomorphic encryption.
另一种可能更严重的攻击是，攻击者以某种方式获得解密某些密文的能力，或收集有关其内容的一些信息（可能通过在解密后观察客户端的外部行为）。这可能使攻击者有可能发起（可能是有限的）选择的密文攻击，从而有可能危及加密数据的安全性。此类攻击没有通过语义安全保证来解决，除了使用同态加密之外，还需要采取其他措施。



#### c. Evaluation Privacy
A desirable additional security property beyond semantic security would be that the ciphertext C hides which computations were performed homomorphically to obtain C. We call this security requirement Evaluation Privacy.
除了语义安全之外，一个理想的附加安全属性是密文 C 隐藏了哪些计算是以同态方式执行以获得 C。我们将此安全要求称为评估隐私。

For example, suppose a cloud service offers a service in the form of computing a proprietary machine learning algorithm 𝐹 on the client’s sensitive data. As before, the client encrypts its data 𝑀 to obtain C and sends the cloud C and the evaluation key EK. The cloud now computes C’ which is an encryption of 𝐹(𝑀) to hand back to the client. Evaluation privacy will guarantee that C’ does not reveal anything about the algorithm 𝐹 which is not derivable from the pair (𝑀, 𝐹(𝑀)). Here we can also distinguish between semi-honest and malicious evaluation privacy depending on whether the ciphertext C is generated correctly according to the Encrypt algorithm.
例如，假设云服务以计算专有机器学习算法 F 的形式提供服务，该算法对客户端的敏感数据进行计算。和以前一样，客户端对其数据 M 进行加密以获取 C，并发送云 C 和评估密钥 EK。云现在计算 C'，这是 F（M） 的加密，以交还给客户端。评估隐私将保证 C' 不会泄露任何关于算法 F 的任何信息，而这些算法 F 不能从对 （M， F（M） ） 中导出。这里我们还可以根据加密算法是否正确生成密文C来区分半诚实和恶意评价隐私。

A weaker requirement would be to require evaluation privacy only with respect to an adversary who does not know the secret decryption key. This may be relevant for an adversary who intercepts encrypted network traffic.
一个较弱的要求是仅要求对不知道秘密解密密钥的对手进行评估隐私。这可能与拦截加密网络流量的对手有关。


#### d. Key Evolution
Say that a corpus of ciphertexts encrypted under a secret key SK is held by a server, and the client who owns SK realizes that SK may have been compromised.

It is desirable for an encryption scheme to have the following key evolution property. Allow the client to generate a new secret key SK’ which replaces SK, a new evaluation key EK’, and a transformation key TK such that: the server, given only TK and EK’, may convert all ciphertexts in the corpus to new ciphertexts which (1) can be decrypted using SK’ and (2) satisfy semantic security even for an adversary who holds SK.
加密方案最好具有以下密钥演化属性。允许客户端生成一个新的密钥 SK' 来替换 SK'、一个新的评估密钥 EK' 和一个转换密钥 TK，这样：服务器，只给出 TK 和 EK'，可以将语料库中的所有密文转换为新的密文，这些密文 （1） 可以使用 SK' 解密，并且 （2） 即使对于持有 SK 的对手也满足语义安全。

Any sufficiently homomorphic encryption scheme satisfies the key evolution property as follows. Let TK be the encryption of SK under SK’. Namely, TK is a ciphertext which when decrypted using secret key SK’ yields SK. A server given TK and EK’, can convert a ciphertext C in the corpus into C’ by homomorphically evaluating the decryption process. Security follows from semantic security of the original homomorphic encryption scheme.
任何足够同态的加密方案都满足密钥演化属性，如下所示。让 TK 成为 SK' 下 SK 的加密。也就是说，TK 是一个密文，当使用密钥 SK' 解密时会产生 SK。给定 TK 和 EK' 的服务器可以通过同态评估解密过程将语料库中的密文 C 转换为 C'。安全性源于原始同态加密方案的语义安全性。


#### e. Side Channel Attacks
Side channel attacks consider adversaries who can obtain partial information about the secret key of an encryption scheme, for example by running timing attacks during the execution of the decryption algorithm. A desirable security requirement from an encryption scheme is resiliency against such attacks, often referred to as leakage resiliency. That is, it should be impossible to violate semantic security even in presence of side channel attacks. Naturally, leakage resilience can hold only against limited information leakage about the secret key. 
侧信道攻击是指可以获取有关加密方案密钥的部分信息的攻击者，例如，通过在执行解密算法期间运行计时攻击。加密方案的一个理想的安全要求是针对此类攻击的复原能力，通常称为泄漏复原能力。也就是说，即使存在侧信道攻击，也应该不可能违反语义安全。当然，泄漏恢复能力只能防止有关密钥的有限信息泄漏。

An attractive feature of encryption schemes based on intractability of integer lattice problems, and in particular known HE schemes based on intractability of integer lattice problems, is that they satisfy leakage resilience to a great extent. This is in contrast to public-key cryptosystems such as RSA.
基于整数格问题的难处理性的加密方案，特别是基于整数格问题的难处理性的已知HE方案，其一个吸引人的特点是它们在很大程度上满足了泄漏弹性。这与 RSA 等公钥密码系统形成鲜明对比。


#### f. Identity Based Encryption
In an identity based encryption scheme it is possible to send encrypted messages to users without knowing either a public key or a secret key, but only the identity of the recipient where the identity can be a legal name or an email address.
在基于身份的加密方案中，可以在不知道公钥或密钥的情况下向用户发送加密消息，而只知道收件人的身份，其中身份可以是法定名称或电子邮件地址。

This is possible as long as there exists a trusted party (TP) that publishes some public parameters PP and holds a master secret key MSK. A user with identity X upon authenticating herself to the TP (e.g. by showing a government issued ID), will receive a secret key SKx that the user can use to decrypt any ciphertext that was sent to the identity X. To encrypt message M to identity X, one needs only to know the public parameters PP and X.
只要存在发布一些公共参数 PP 并持有主密钥 MSK 的受信任方 （TP），这是可能的。身份为 X 的用户在向 TP 进行身份验证时（例如，通过出示政府颁发的 ID），将收到一个密钥 SKx，用户可以使用该密钥解密发送给身份 X 的任何密文。要将消息 M 加密为身份 X，只需知道公共参数 PP 和 X。

Identity based homomorphic encryption is a variant of public key homomorphic encryption which may be desirable.
基于身份的同态加密是公钥同态加密的一种变体，这可能是可取的。

Remark: A modification of GSW supports identity based homomorphic encryption.
备注：GSW的修改支持基于身份的同态加密。


## Homomorphic Encryption Standard Section 2.1 Recommended Security Parameters

### Section 2.1.1. Hard Problems
This section describes the computational problems whose hardness form the basis for the security of the homomorphic encryption schemes in this document. Known security reductions to other problems are not included here. Section 2.1.2 below describes the best currently known attacks on these problems and their concrete running times. Section 2.1.5 below recommends concrete parameter choices to achieve various security levels against currently known attacks.
本节介绍本文档中构成同态加密方案安全性基础的硬度的计算问题。此处不包括对其他问题的已知安全性降低。下面的第 2.1.2 节描述了针对这些问题的当前已知的最佳攻击及其具体运行时间。下面的第 2.1.5 节建议了具体的参数选择，以实现针对当前已知攻击的各种安全级别。


#### a. The Learning with Errors (LWE) Problem
The LWE problem is parametrized by four parameters (𝑛, 𝑚, 𝑞, 𝜒), where 𝑛 is a positive integer referred to as the “dimension parameter”, m is “the number of samples”, 𝑞 is a positive integer referred to as the “modulus parameter” and 𝜒 is a probability distribution over rational integers referred to as the “error distribution”.
LWE 问题由四个参数（n、m、q、χ）参数化，其中 n 是正整数，称为“维度参数”，m 是“样本数”，q 是正整数，称为“模参数”，χ 是有理整数的概率分布，称为“误差分布”。

The LWE assumption requires that the following two probability distributions are computationally indistinguishable:
LWE 假设要求以下两个概率分布在计算上是不可区分的：

Distribution 1. Choose a uniformly random matrix 𝑚 × 𝑛 matrix 𝐴, a uniformly random vector 𝑠 from the vector space 𝑍𝑞𝑛, and a vector 𝑒 from 𝑍𝑚 where each coordinate is chosen from the error distribution 𝜒. Compute 𝑐 ∶= 𝐴𝑠 + 𝑒, where all computations are carried out modulo 𝑞. Output (𝐴, 𝑐). 选择一个均匀随机矩阵 m × n 个矩阵 A，从向量空间 Zqn 中选择一个均匀随机向量 s，从 Zm 中选择一个向量 e，其中每个坐标都是从误差分布 χ 中选择的。计算 c ∶= As + e，其中所有计算都是以模 q 进行的。输出 （A， c）。

Distribution 2. Choose a uniformly random 𝑚 × 𝑛 matrix 𝐴, and a uniformly random vector 𝑐 from 𝑍𝑞𝑚. Output (𝐴, 𝑐).从 Zqm 中选择一个均匀随机的 m × n 矩阵 A，以及一个均匀随机的向量 c。输出 （A， c）。

The error distribution 𝜒 can be either a discrete Gaussian distribution over the integers, a continuous Gaussian distribution rounded to the nearest integer, or other distributions supported on small integers. We refer the reader to Section 2.1.5 for more details on particular error distributions, algorithms for sampling from these distributions, and the associated security implications. We also mention that the secret vector s can be chosen from the error distribution.
误差分布 χ 可以是整数上的离散高斯分布、四舍五入到最接近整数的连续高斯分布，也可以是小整数上支持的其他分布。我们请读者参阅第 2.1.5 节，了解有关特定错误分布、从这些分布中采样的算法以及相关安全隐患的更多详细信息。我们还提到，可以从误差分布中选择秘密向量 s。


#### b. The Ring Learning with Errors (RLWE) Problem
The RLWE problem can be viewed as a specific case of LWE where the matrix 𝐴 is chosen to have special algebraic structure. RLWE is parametrized by parameters (𝑚, 𝑞, 𝜒) where 𝑚 is the number of samples, as in the LWE problem above, 𝑞 is a positive integer (the “modulus parameter”) and 𝜒 is a probability distribution over the ring 𝑅 = 𝑍[𝑋]/𝑓(𝑋) (the “error distribution”).
RLWE 问题可以看作是 LWE 的一个特殊情况，其中矩阵 A 被选择为具有特殊代数结构。RLWE 由参数 （m， q， χ） 参数化，其中 m 是样本数，如上面的 LWE 问题，q 是正整数（“模参数”），χ 是环 R = Z[X]/f（X） 上的概率分布（“误差分布”）。

The RLWE assumption requires that the following two probability distributions are computationally indistinguishable:
Distribution 1. Choose 𝑚 + 1 uniformly random elements 𝑠, 𝑎1, … , 𝑎𝑚 from the ring 𝑅/𝑞𝑅, and 𝑚 more elements 𝑒1, … , 𝑒𝑚 from the ring 𝑅 chosen from the error distribution 𝜒. Compute 𝑏𝑖 ∶= 𝑠𝑎𝑖 + 𝑒𝑖, all computations carried out over the ring 𝑅/𝑞𝑅. Output {(𝑎𝑖, 𝑏𝑖) ∶ 𝑖 = 1, … 𝑚}.

Distribution 2. Choose 2m uniformly random elements 𝑎1, … , 𝑎𝑚, 𝑏1, … , 𝑏𝑚 from the ring 𝑅/𝑞𝑅. Output {(𝑎𝑖, 𝑏𝑖) ∶ 𝑖 = 1, … 𝑚}.

The error distribution χ must be supported on “small” elements in the ring R (with geometry induced by the canonical embedding). For RLWE, it is important to use an error distribution that matches the specific ring 𝑅. See Section 2.1.5 for more details on the error distributions, algorithms for sampling from these distributions, and the associated security implications. Here too, the secret element s can be chosen from the error distribution.
误差分布 χ 必须支持环 R 中的“小”单元（具有由规范嵌入引起的几何形状）。对于 RLWE，使用与特定环 R 匹配的误差分布非常重要。有关错误分布、从这些分布中采样的算法以及相关的安全隐患的更多详细信息，请参见第 2.1.5 节。在这里，也可以从错误分布中选择秘密元素 s。


#### c. The Module Learning with Errors (RLWE) Problem
We mention here that there is a general formulation of the learning with errors problem that captures both LWE and RLWE, as well as many other settings. In this formulation, rather than 𝑛-vectors over 𝑍 (as in LWE) or 1-vectors over 𝑅 = 𝑍[𝑥]/𝑓(𝑋) (as in RLWE), we work with vectors of dimension 𝑛1 over a ring of dimension 𝑛2, where the security parameter is related to 𝑛1 ⋅ 𝑛2. This document only deals with LWE and RLWE, but we expect future versions to be extended to deal with more settings.
我们在这里提到，有一个错误学习问题的一般表述，它同时捕获了 LWE 和 RLWE，以及许多其他设置。在这个公式中，我们不是在 Z 上使用 n 向量（如在 LWE 中）或在 R = Z[x]/f（X） 上是 1 向量（如在 RLWE 中），而是在维数为 n2 的环上处理维数为 n1 的向量，其中安全参数与 n1 ⋅ n2 相关。本文档仅涉及 LWE 和 RLWE，但我们预计未来的版本将扩展以处理更多设置。


### Section 2.1.2 Attacks on LWE and their Complexity
We review algorithms for solving the LWE problem and use them to suggest concrete parameter choices. The schemes described above all have versions based on the LWE and the RLWE assumptions. When the schemes based on RLWE are instantiated with error distributions that match the cyclotomicrings (as described later in this document), we do not currently have attacks on RLWE that are meaningfully better than the attacks on LWE. The following estimates and attacks refer to attacks on the LWE problem with the specified parameters.
我们回顾了解决 LWE 问题的算法，并使用它们来建议具体的参数选择。上述方案都具有基于LWE和RLWE假设的版本。当基于RLWE的方案被实例化为与环形组学相匹配的错误分布时（如本文档后面所述），我们目前没有对RLWE的攻击比对LWE的攻击更好。以下估计和攻击是指使用指定参数对 LWE 问题进行的攻击。

Much of this section is based on the paper by Albrecht, Player, and Scott (Albrecht, Player, & Scott, 2015), the online Estimator tool which accompanies that paper, and (Albrecht, 2017; Albrecht, Göpfert, Virdia, & Wunderer, 2017). Indeed, we reuse text from those works here. Estimated security levels in all the tables in this section were obtained by running the Estimator based on its state in March 2018. The tables in this section give the best attacks (in terms of running time expressed in 𝑙𝑜𝑔2) among all known 
attacks as implemented by the Estimator tool. As attacks or implementations of attacks change, or as new attacks are found, these tables will need to be updated. First, we describe all the attacks which give the best running times when working on parameter sizes in the range which are interesting for Homomorphic Encryption.
本节的大部分内容基于Albrecht，Player和Scott（Albrecht，Player和Scott，2015）的论文，该论文随附的在线估算工具，以及（Albrecht，2017;Albrecht，Göpfert，Virdia和Wunderer，2017）。事实上，我们在这里重复使用了这些作品中的文本。本部分中所有表中的估计安全级别是通过在 2018 年 3 月根据其状态运行 Estimator 获得的。本节中的表格给出了所有已知攻击中最好的攻击（以 log2 表示的运行时间）
Estimator 工具实现的攻击。随着攻击或攻击实现的变化，或者发现新的攻击，这些表将需要更新。首先，我们描述了所有攻击，这些攻击在处理参数大小时提供最佳运行时间，这对同态加密来说很有趣。

The LWE problem asks to recover a secret vector 𝑠 ∈ 𝑍𝑞𝑛, given a matrix 𝐴 ∈ 𝑍𝑞𝑚×𝑛 and a vector 𝑐 ∈ 𝑍𝑞𝑚 such that 𝐴𝑠 + 𝑒 = 𝑐 𝑚𝑜𝑑 𝑞 for a short error vector 𝑒 ∈ 𝑍𝑞𝑚 sampled coordinate-wise from an error distribution 𝜒. The decision variant of LWE asks to distinguish between an LWE instance (𝐴, 𝑐) and uniformly random (𝐴, 𝑐) ∈ 𝑍𝑞𝑚×𝑛 × 𝑍𝑞𝑚. To assess the security provided by a given set of parameters 𝑚, 𝜒, 𝑞, two strategies are typically considered.

The primal strategy finds the closest vector to 𝑐 in the integral span of columns of 𝐴 mod 𝑞, i.e. it solves the corresponding Bounded Distance Decoding problem (BDD) directly as is explained in [LP11] and [LL15].


#### a. Primal (uSVP variant)
Assume that m > n, i.e. the number of samples available is greater than the dimension of the lattice. Writing $[𝐼_𝑛|𝐴′]$ for the reduced row echelon form of $𝐴^𝑇 ∈ 𝑍_𝑞^{𝑛×𝑚}$ (with high probability and after appropriate permutation of columns), this task can be reformulated as solving the unique Shortest Vector Problem (uSVP) in the 𝑚 + 1 dimensional 𝑞-ary lattice 

$$𝛬 = 𝑍^{𝑚+1} ⋅ 
\begin{pmatrix}
𝐼_𝑛 & 𝐴^′ & 0 \\
0 & 𝑞𝐼_{𝑚−𝑛} &  0 \\
𝑐^𝑇 & & 𝑡\end{pmatrix}. $$

by Kannan’s embedding, with embedding factor 𝑡.

The lattice 𝛬 has volume $𝑡 ⋅ 𝑞^{𝑚−𝑛} $and contains a vector of norm $\sqrt{\|𝑒\|^2+ 𝑡^2}$ which is unusually short, i.e. the gap between the first and second Minkowski minimum $𝜆_2(𝛬)/⁄𝜆_1(𝛬)$ is large. If the secret vector 𝑠 is also short, there is a second established embedding reducing LWE to uSVP. By inspection, it can be seen that the vector (𝜈𝑠|𝑒|1), for some 𝜈 ≠ 0, is contained in the lattice 𝛬 of dimension 𝑑 = 𝑚 + 𝑛 + 1 

$$𝛬 = \{𝑥 ∈ (𝜈𝑍)^𝑛 × 𝑍^{𝑚+1} | 𝑥 ⋅ (\frac1𝜈 𝐴|𝐼_𝑚| − 𝑐)^⊤ ≡ 0  \bmod 𝑞\},$$

where 𝜈 allows to balance the size of the secret and the noise. An (𝑛 + 𝑚 + 1) × (𝑛 + 𝑚 + 1) basis 𝑀 for 𝛬 can be constructed as 

$$𝑀 = 
\begin{pmatrix}
𝜈𝐼_𝑛 & −𝐴^⊤ & 0 \\
0 & 𝑞𝐼_𝑚 & 0 \\
0 & 𝑐 & 1
\end{pmatrix}$$.

To find short vectors, lattice reduction can be applied. Thus, to establish the cost of solving an LWE instance, we may consider the cost of lattice reduction for solving uSVP. In (Alkim, Ducas, Pöppelmann, & Schwabe, 2016) it is predicted that 𝑒 can be found if:

$$\sqrt{𝛽⁄𝑑} \| (𝑒|1) \| ≈ \sqrt𝛽𝜎 ≤ 𝛿_0^{2𝛽−𝑑} 𝑉𝑜𝑙(𝛬)^{1⁄𝑑},$$

where $𝛿_0$ denotes the root Hermite factor achievable by BKZ, which depends on 𝛽 which is the block size of the underlying blockwise lattice reduction algorithm. This prediction was experimentally verified in (Albrecht et al., 2017).


#### b. Primal by BDD Enumeration (decoding).
This attack is due to Lindner and Peikert [LP11]. It starts with a sufficiently reduced basis, e.g., using BKZ in block size 𝛽, and then applies a modified version of the recursive Nearest Plane algorithm due to Babai [Bab86]. Given a basis 𝐵 and a target vector 𝑡, the Nearest Plane algorithm finds a vector such that the error vector lies in the fundamental parallelepiped of the Gram-Schmidt orthogonalization (GSO) of 𝐵.
这次攻击是由于 Lindner 和 Peikert [LP11] 造成的。它从充分简化的基础开始，例如，在块大小β中使用 BKZ，然后应用由于 Babai [Bab86] 而递归最近平面算法的修改版本。给定基 B 和目标向量 t，最近平面算法找到一个向量，使得误差向量位于 B 的 Gram-Schmidt 正交化 （GSO） 的基本平行六面体中。

Lindner and Peikert note that for a BKZ-reduced basis 𝐵, the fundamental parallelepiped is long and thin, by the Geometric Series Assumption (GSA) due to Schnorr that the GSO of a BKZ-reduced basis decay geometrically and this makes the probability that the Gaussian error vector 𝑒 falls in the corresponding fundamental parallelepiped very low. To improve this success probability, they “fatten” the parallelepiped by essentially scaling its principal axes. They do this by running the Nearest Plane algorithm on several distinct planes at each level of recursion. For a Gaussian error vector, the probability that it falls in this fattened parallelepiped is expressed in terms of the scaling factors and the lengths of the GSO of 𝐵. This can be seen as a form of pruned CVP enumeration (Liu & Nguyen, 2013).
Lindner 和 Peikert 指出，对于 BKZ 约简基 B，基本平行六面体又长又细，根据几何级数假设 （GSA），由于 Schnorr 认为 BKZ 约简基的 GSO 在几何上衰减，这使得高斯误差向量 e 落在相应基本平行六面体中的概率非常低。为了提高这种成功概率，他们通过基本上缩放平行六面体的主轴来“增肥”平行六面体。他们通过在每个递归级别的几个不同平面上运行最近平面算法来实现这一点。对于高斯误差向量，它落入这个肥大的平行六面体的概率用比例因子和 B 的 GSO 长度表示。这可以看作是修剪CVP枚举的一种形式（Liu&Nguyen，2013）。

The run time of the Nearest Planes algorithm mainly depends on the number of points enumerated, which is the product of the scaling factors. The run time of the basis reduction step depends on the quality of the reduced basis, expressed, for instance, by the root Hermite factor 𝛿0. The scaling factors and the quality of the basis together determine the success probability of the attack. Hence to maximize the success probability, the scaling factors are determined based on the (predicted) quality of the BKZ￾reduced basis. There is no closed formula for the scaling factors. The Estimator uses a simple greedy algorithm to find these parameters due to ([LP11]), but this is known to not be optimal. The scaling factors and the quality of the basis are chosen to achieve a target success probability and to minimize the running time (by balancing the running time of BKZ reduction and the final enumeration step).
最近平面算法的运行时间主要取决于枚举的点数，点数是比例因子的乘积。基数还原步骤的运行时间取决于还原基的质量，例如，由根 Hermite 因子 δ0 表示。比例因子和基数的质量共同决定了攻击的成功概率。因此，为了最大限度地提高成功概率，比例因子是根据 BKZreduced 基的（预测）质量确定的。比例因子没有封闭的公式。由于 （[LP11]），Estimator 使用简单的贪婪算法来查找这些参数，但已知这不是最优的。选择比例因子和基础质量以实现目标成功概率并最小化运行时间（通过平衡 BKZ 减少的运行时间和最终枚举步骤）。


#### c. Dual.
The dual strategy finds short vectors in the lattice

$$𝑞𝛬∗ = {𝑥 ∈ 𝑍𝑞𝑚 | 𝑥 ⋅ 𝐴 ≡ 0 𝑚𝑜𝑑 𝑞}$$,

i.e. it solves the Short Integer Solutions problem (SIS). Given such a short vector 𝑣, we can decide if an instance is LWE by computing ⟨𝑣, 𝑐⟩ = ⟨𝑣, 𝑒⟩ which is short whenever 𝑣 and 𝑒 are sufficiently short (Micciancio & Regev, 2009).
即它解决了短整数解问题 （SIS）。给定这样一个短向量 v，我们可以通过计算 ⟨v， c⟩ = ⟨v， e⟩ 来判断一个实例是否是 LWE，只要 v 和 e 足够短，它就会很短（Micciancio & Regev，2009）。

We must however ensure that ⟨𝑣, 𝑒⟩ indeed is short enough, since if is too large, the (Gaussian) distribution of will be too flat to distinguish from random. Following ([LP11]), for an LWE instance with parameters 𝑛, 𝛼, 𝑞 and a vector 𝑣 of length ∥ 𝑣 ∥ such that 𝑣 ⋅ 𝐴 ≡ 0 𝑚𝑜𝑑 𝑞, the advantage of distinguishing ⟨𝑣, 𝑒⟩ from random is close to

$$𝑒𝑥𝑝(−𝜋(∥ 𝑣 ∥⋅ 𝛼)^2)$$.

To produce a short enough 𝑣, we may again call a lattice-reduction algorithm. In particular, we may call the BKZ algorithm with block size 𝛽. After performing BKZ-𝛽 reduction the first vector in the transformed lattice basis will have norm $𝛿_0^𝑚 ⋅ 𝑉𝑜𝑙(𝑞𝛬^∗)^{1/𝑚}$. In our case, the expression above simplifies to $\|𝑣\|≈ 𝛿_0^𝑚 ⋅ 𝑞^{𝑛⁄𝑚} $ whp. The minimum of this expression is attained at $𝑚 = \sqrt{\frac{𝑛\log𝑞}{\log𝛿_0}}$ (Micciancio & Regev, 2009). The attack can be modified to take small or sparse secrets into account (Albrecht, 2017).


#### Lattice Reduction algorithm: BKZ
BKZ is an iterative, block-wise algorithm for basis reduction. It requires solving the SVP problem (using sieving or enumeration, say) in a smaller dimension 𝛽, the block size. First, the input lattice 𝛬 is LLL reduced, giving a basis $𝑏_0, … , 𝑏_{𝑛−1}$. For 0 ≤ 𝑖 < 𝑛, the vectors $𝑏_𝑖, … , 𝑏_{𝑚𝑖𝑛(𝑖+𝛽−1,𝑛−1)}$ are projected onto the orthogonal complement of the span of $𝑏_0, … , 𝑏_{𝑖−1}$; this projection is called a local block. In the local block, we find a shortest vector, view it as a vector 𝑏 ∈ 𝛬 of and perform LLL on the list of vectors $𝑏_𝑖, … , 𝑏_{𝑚𝑖𝑛(𝑖+𝛽−1,𝑛−1)}$, 𝑏 to remove linear dependencies. We use the resulting vectors to update $𝑏_𝑖, … , 𝑏_{𝑚𝑖𝑛(𝑖+𝛽−1,𝑛−1)}$. This process is repeated until a basis is not updated after a full pass.

There have been improvements to BKZ, which are collectively referred to BKZ 2.0 (see [CN11] for example). There are currently several different assumptions in the literature about the cost of running BKZ, distinguished by how conservative they are, the “sieve” and “ADPS16” cost models, as explained below. In our use of the Estimator we rely on the cost model in the “sieve” implementation, as it seems the most relevant to the parameter sizes which we use for Homomorphic Encryption.
对 BKZ 进行了改进，这些改进统称为 BKZ 2.0（例如，参见 [CN11]）。目前，文献中有几种关于运行 BKZ 成本的不同假设，其特点是它们的保守程度，即“筛子”和“ADPS16”成本模型，如下所述。在使用 Estimator 时，我们依赖于“筛子”实现中的成本模型，因为它似乎与我们用于同态加密的参数大小最相关。

##### a. Block Size.
To establish the required block size 𝛽, we solve
$$\log 𝛿_0 = \log (\frac𝛽{2𝜋𝑒} (𝜋𝛽)^{1/𝛽}) ⋅ \frac1{2(𝛽− 1)}$$

for 𝛽, see the PhD Thesis of Yuanmi Chen (Chen, 2013) for a justification of this.


##### b. Cost of SVP.
Several algorithms can be used to realize the SVP oracle inside BKZ. Asymptotically, the fastest known 
algorithms are sieving algorithms. The fastest, known classical algorithm runs in time 
$2^{0.292𝛽+𝑜(𝛽)}$ (Becker, Ducas, Gama, & Laarhoven, 2016).

The fastest, known quantum algorithm runs in time
$2^{0.265𝛽+𝑜(𝛽)}$ (Laarhoven, 2015).

The “sieve” estimate approximates 𝑜(𝛽) by 16.4 based on some experimental evidence in (Becker et al., 2016). The “ADPS16” from (Alkim et al., 2016) suppresses the 𝑜(𝛽) term completely. All times are expressed in elementary bit operations.
根据一些实验证据，“筛子”估计值近似 o（β） 16.4（Becker 等人，2016 年）。（Alkim等人，2016）的“ADPS16”完全抑制了o（β）项。所有时间均以基本位运算表示。


##### c. Calls to SVP.
The BKZ algorithm proceeds by repeatedly calling an oracle for computing a shortest vector on a smaller lattice of dimension 𝛽. In each “tour” on a 𝑑-dimensional lattice, 𝑑 such calls are made and the algorithm is typically terminated once it stops making sufficient progress in reducing the basis. Experimentally, it has been established that only the first few tours make significant progress (Chen, 2013), so the “sieve” cost model assumes that one BKZ call costs as much as 8𝑑 calls to the SVP oracle. However, it seems plausible that the cost of these calls can be amortized across different calls, which is why the “ADPS16” cost model from (Alkim et al., 2016) assumes the cost of BKZ to be the same as oneSVP oracle call, which is a strict underestimate of the attack cost.
BKZ 算法通过重复调用预言机来计算维数 β 的较小晶格上的最短向量。在d维晶格上的每个“巡视”中，都会进行d次这样的调用，并且一旦算法在减少基数方面停止取得足够的进展，该算法通常会终止。通过实验，已经确定只有前几次巡视取得了重大进展（Chen，2013），因此“筛子”成本模型假设一次BKZ调用的成本与对SVP预言机的8d调用一样多。然而，这些调用的成本可以在不同的调用中摊销，这似乎是合理的，这就是为什么（Alkim et al.， 2016）的“ADPS16”成本模型假设 BKZ 的成本与 oneSVP 预言机调用相同，这是对攻击成本的严格低估。


##### d. BKZ Cost.
In summary:
**sieve**
a call to BKZ-𝛽 costs $8𝑑⋅2^{0.292𝛽+16.4}$ operations classically and $8𝑑⋅2^{0.265𝛽+16.4}$ operations quantumly.

**ADPST16**
a call to BKZ-𝛽 costs 20.292𝛽 operations classically and 20.265𝛽 operations quantumly.

We stress that both of these cost models are very conservative, and that no known implementation of lattice reduction achieves these running times. Furthermore, these estimates completely ignore memory consumption, which, too, is 2𝛩(𝛽).


##### e. Calls to BKZ.
To pick parameters, we normalize running times to a fixed success probability. That is, all our expected costs are for an adversary winning with probability 51%. However, as mentioned above, it is often more efficient to run some algorithm many times with parameters that have a low probability of success instead of running the same algorithm under parameter choices which ensure a high probability of success. 
为了选择参数，我们将运行时间归一化为固定的成功概率。也就是说，我们所有的预期成本都是对手以 51% 的概率获胜。然而，如上所述，使用成功概率较低的参数多次运行某些算法通常比在确保成功概率高的参数选择下运行相同的算法更有效。


### 2.1.3 The Arora-Ge Attack.
The effectiveness of the lattice attacks above depend on the size of the error and the modulus 𝑞, in contrast Arora and Ge described in [AG11] an attack whose complexity depends only on the size of the error and poly-logarithmically on the modulus 𝑞. Very roughly, for dimension 𝑛 and noise of magnitude bounded by some positive integer 𝑑 in each coordinate, the attack uses $𝑛^{𝑂(𝑑)}$ samples and takes $𝑛^{𝑂(𝑑)}$ operations in the ring of integers modulo 𝑞. For the relevant range of parameters for homomorphic encryption, this attack performs worse than the above lattice attacks even when the error standard deviation is a small constant (e.g., 𝜎 = 2).


### 2.1.4 Algebraic Attacks on instances of Ring-LWE
In practice the ring R is taken to be the ring of integers in a cyclotomic field, $𝑅 = 𝑍[𝑥]/\Phi_𝑘(𝑥)$, where $\Phi_𝑘$ is the cyclotomic polynomial for the cyclotomic index 𝑘, and the degree of $\Phi_𝑘$ is equal to the dimension of the lattice, $𝑛 = \Phi(𝑘)$ where $\Phi$ is the Euler totient function. 

As mentioned above, for ring-LWE the choice of the error distribution matters, and there are known examples of natural high-entropy error distributions that are insecure to use in certain rings. Such examples were first given in [ELOS15] and [CLS15], and were subsequently improved in [CIV16a], [CIV16b], and [CLS16]. For example, in [CLS15] it was shown that for a prime cyclotomic index 𝑚, choosing the coefficients of the error polynomial $𝑒 ∈ 𝑍[𝑥]/\Phi_𝑘(𝑥)$ independently at random from a distribution of standard deviation sufficiently smaller than $\sqrt𝑘$, can sometimes make this instance of RLWE easy to solve. It is therefore crucial to select an error distribution that “matches” the ring at hand.
如上所述，对于环LWE，误差分布的选择很重要，并且有一些已知的自然高熵误差分布的例子，在某些环中使用是不安全的。这些例子首先在[ELOS15]和[CLS15]中给出，随后在[CIV16a]、[CIV16b]和[CLS16]中得到改进。例如，在 [CLS15] 中表明，对于素数旋风指数 m，从足够小于 $sqrtk$ 的标准差分布中随机随机选择误差多项式 𝑒 ∈ 𝑍[𝑥]/\Phi_𝑘(𝑥)$ 的系数，有时可以使这个 RLWE 实例易于求解。因此，选择与手头的环“匹配”的误差分布至关重要。

The form of the error distribution for general cyclotomic rings was investigated, e.g., in [LPR13, DD12, LPR13b, P16]. We summarize these results in Section 2.1.5 below, but the current document only specifies concrete parameters for power-of-two cyclotomic fields, i.e. $𝑘 = 2^ℓ$. We expect future versions of this document to extend the treatment also for generic cyclotomic rings. We stress that when the error is chosen from a sufficiently wide and “well spread” distributions that match the ring at hand, we do not have meaningful attacks on RLWE that are better than LWE attacks, regardless of the ring. For power-of-two cyclotomics, it is sufficient to sample the noise in the polynomial basis, namely choosing the coefficients of the error polynomial $𝑒 ∈ 𝑍[𝑥]/\Phi_𝑘(𝑥)$ independently at random from a very “narrow” distribution.
研究了一般环形环的误差分布形式，例如在[LPR13，DD12，LPR13b，P16]中。我们在下面的第 2.1.5 节中总结了这些结果，但当前文档仅指定了 2 次幂循环场的具体参数，即 $𝑘 = 2^ℓ$. 我们预计本文档的未来版本也将扩展通用环的治疗范围。我们强调，当误差是从与手头的环相匹配的足够宽且“分布良好”的分布中选择的时，无论环如何，我们都没有比 LWE 攻击更好的有意义的 RLWE 攻击。对于二次幂的循环组学，在多项式基中对噪声进行采样就足够了，即从非常“窄”的分布中随机随机选择误差多项式$𝑒 ∈ 𝑍[𝑥]/\Phi_𝑘(𝑥)$ 的系数就足够了。


### 2.1.5 Secure Parameter Selection for Ring LWE
Specifying a Ring-LWE scheme for encryption requires specifying a ring, 𝑅, of a given dimension, 𝑛, along with a ciphertext modulus 𝑞, and a choice for the error distribution and a choice for a secret distribution. 
指定用于加密的 Ring-LWE 方案需要指定给定维度 n 的环 R 以及密文模数 q，以及错误分布的选择和秘密分布的选择。

**Ring.** In practice, we take the ring 𝑅 to be a cyclotomic ring 𝑅 = 𝑍[𝑥]/Φ𝑘(𝑥), where 𝑚 is the cyclotomic index and 𝑛 = 𝜙(𝑘) is the ring dimension. For example, a power of 2 cyclotomic with index $𝑘 = 2^ℓ$ is $𝑅 = 𝑍[𝑥]/(𝑥^{𝑘/2} + 1)$, of degree $𝑛 = 𝑘/2 = 2^{ℓ−1}$. 

**Error distribution, power-of-two cyclotomics.** For the special case of power-of-two cyclotomics, it is safe to sample the error in the polynomial basis, namely choosing the coefficients of the error polynomial $𝑒(𝑥) ∈ 𝑍[𝑥]/(𝑥^{𝑘/2} + 1)$ independently at random from a very “narrow” distribution. Specifically, it is sufficient to choose each coefficient from a Discrete Gaussian distribution (or even rounded continuous Gaussian distribution) with a small constant standard deviation 𝜎. Selecting the error according to a Discrete Gaussian distribution is described more often in the literature, butchoosing from a rounded continuous Gaussian is easier to implement (in particular when timing attacks need to be countered).
误差分布，二次幂循环组学。对于二次幂循环组学的特殊情况，在多项式基中对误差进行采样是安全的，即从非常“窄”的分布中随机随机选择误差多项式 $𝑒(𝑥) ∈ 𝑍[𝑥]/(𝑥^{𝑘/2} + 1)$ 的系数。具体来说，从离散高斯分布（甚至四舍五入连续高斯分布）中选择每个系数就足够了，σ具有较小的恒定标准差。根据离散高斯分布选择误差在文献中更常见，但从四舍五入的连续高斯分布中选择更容易实现（特别是当需要反击时序攻击时）。

The LWE attacks mentioned above, however, do not take advantage of the shape of the error distribution, only the standard deviation. Moreover, the security reductions do not apply to the case where the error standard deviation is a small constant and would instead require that the error standard deviation grows at least as $𝑛^𝜖$ for some constant 𝜖 > 1/2 (or even 𝜖 > 3/4). The analysis of the security levels given below relies on running time estimates which assume that the shape of the error distribution is Gaussian.
然而，上面提到的 LWE 攻击并没有利用误差分布的形状，而只利用了标准差。此外，安全性降低不适用于误差标准差为小常数的情况，而是要求误差标准差至少增长为 $n^ε$ 对于某个常数ε > 1/2（甚至ε > 3/4）。下面给出的安全级别分析依赖于运行时间估计，该估计假设误差分布的形状为高斯分布。

The standard deviation that we use below is chosen as $𝜎 = 8/\sqrt{2𝜋} ≈ 3.2$, which is a value that is used in many libraries in practice and for which no other attacks are known. (Some proposals in the literature suggest even smaller values of 𝜎.) Over time, if our understanding of the error standard deviationimproves, or new attacks are found, the standard deviation of the error may have to change.
我们在下面使用的标准差被选为$𝜎 = 8/\sqrt{2𝜋} ≈ 3.2$，这是许多库在实践中使用的值，并且没有其他已知的攻击。（文献中的一些建议甚至更小的σ值。随着时间的流逝，如果我们对误差标准差的理解有所提高，或者发现了新的攻击，则误差的标准差可能不得不改变。

**Error distribution, general cyclotomics.** For non-power-of-two cyclotomics, choosing a spherical error in the polynomial basis (i.e., choosing the coefficients independently) may be insecure. Instead, there are two main methods of choosing a safe error polynomial for the general case:
对于非二次幂的循环组式，在多项式基中选择球面误差（即独立选择系数）可能是不安全的。相反，对于一般情况，有两种主要方法可以选择安全误差多项式：
- The method described in [DD12] begins by choosing an “extended” error polynomial $𝑒^′ ∈ 𝑸[𝑋]/(Θ_𝑘(𝑥))$, where $Θ𝑘(𝑥) = 𝑥^𝑘 − 1$ if 𝑘 is odd, and $𝑥^{𝑘/2}$ + 1 if 𝑘 is even. The rational coefficients of 𝑒′ are chosen independently at random from the continuous Gaussian of standard deviation $𝜎\sqrt𝑘$ (for the same 𝜎 as above), and with sufficient precision, e.g., using double float numbers. Then, the error is computed as $$𝑒 = Round(𝑒^′ \mod Φ_𝑘(𝑥))$$

- The method described in [CP16] chooses an error of the form $𝑒 = Round(𝑒^′ ⋅ 𝑡_𝑘)$, where $𝑡_𝑘 ∈ 𝑅$ is a fixed ring element (see below), and 𝑒′ is chosen from a spherical continuous Gaussian distribution in the canonical embedding, of standard deviation 𝜎 (for the same 𝜎 as above). One way of sampling such error polynomial is to choose a spherical 𝑒′ in the canonical embedding, then multiply by 𝑡𝑘 and round, but there are much more efficient methods of sampling the error (cf. [CP16]).
Note that the error so generated may not be very small, since 𝑡𝑘 is not tiny. It is possible to show that 𝑒 is somewhat small, but moreover it is shown in [CP16] that homomorphic computations can be carried out to maintain the invariant that 𝑒/𝑡𝑘 is small (rather than the invariant that 𝑒 itself is small).
请注意，这样产生的错误可能不是很小，因为 tk 并不小。可以证明 e 有点小，但 [CP16] 中表明，可以进行同态计算来保持 e/tk 很小的不变量（而不是 e 本身很小的不变量）。
The element 𝑡𝑘 is a generator of the “different ideal”, and it is only defined up to multiplication by a unit, so implementations have some choice for which specific element to use. One option is 𝑡𝑘(𝑥) = Φ𝑘′ (𝑥) (i.e., the formal derivative of Φ𝑘(𝑥)), but other options may lead to more efficient implementations.
元素 tk 是“不同理想”的生成器，它只被定义为乘以一个单位，因此实现可以选择使用哪个特定元素。一种选择是 tk（x） = Φk′ （x）（即 Φk（x） 的形式导数），但其他选择可能会导致更有效的实现。

We stress that this document does not make recommendations on the specific parameters to use for non-power-of-two cyclotomic rings, in particular Tables 1-4 below only apply to power-of-two cyclotomic rings.
我们强调，本文件并未就用于非两次幂环的具体参数提出建议，特别是下表1-4仅适用于两次幂环。

**Secret key.** For most homomorphic encryption schemes, not only the error but also the secret key must be small. The security reductions ensure that choosing the key from the same distribution as the error does not weaken the scheme. However, for many homomorphic encryption schemes (including BGV and BFV), choosing an even smaller secret key has a significant performance advantage. For example, one may choose the secret key from the ternary distribution (i.e., each coefficient is chosen uniformly from {−1,0,1}). In the recommended parameters given below, we present tables for three choices of secret￾distribution: uniform, the error distribution, and ternary.
对于大多数同态加密方案，不仅错误，而且密钥也必须很小。安全性降低可确保从与错误相同的发行版中选择密钥不会削弱方案。然而，对于许多同态加密方案（包括 BGV 和 BFV），选择更小的密钥具有显着的性能优势。例如，可以从三元分布中选择密钥（即，每个系数都是从 {−1,0,1} 中均匀选择的）。在下面给出的推荐参数中，我们提供了三种秘密分布选择的表格：均匀分布、误差分布和三元分布。

In some extreme cases, there is a reason to choose an even smaller secret key, e.g., one with sparse coefficient vector. However, we will not present tables for sparse secrets because the security implications of using such sparse secrets is not well understood yet. We expect to specify concrete parameters for sparse secret keys in future versions of this standard.
在某些极端情况下，有理由选择更小的密钥，例如具有稀疏系数向量的密钥。但是，我们不会提供稀疏机密的表，因为尚不了解使用此类稀疏机密的安全含义。我们希望在此标准的未来版本中为稀疏密钥指定具体参数。

**Number of samples.** For most of the attacks listed in the tables below, the adversary needs a large number of LWE samples to apply the attack with maximum efficiency. Collecting many samples may be feasible in realistic systems, since from one ring-LWE sample one can extract many “LWE-like” samples. The evaluation keys may also contain some samples.
对于下表中列出的大多数攻击，攻击者需要大量 LWE 样本才能以最高效率应用攻击。在实际系统中收集许多样品可能是可行的，因为从一个环状LWE样品中可以提取许多“类LWE”样品。评估密钥还可能包含一些示例。

**Sampling Methods.** All the error distributions mentioned above require choosing the coefficients of some initial vector independently at random from either the discrete or the continuous Gaussian with some standard deviation 𝜎 > 0. Sampling from a continuous Gaussian with small parameter is quite straightforward, but sampling from a discrete Gaussian distribution is harder. There are several known methods to sample from a discrete Gaussian, including rejection sampling, inversion sampling, Discrete Zuggurat, Bernoulli-type, Knuth-Yao and Von Neumann-type. For efficiency, we recommend the Von Neumann-type sampling method introduced by Karney in [Kar16]. 
上面提到的所有误差分布都需要从离散或连续高斯中随机选择一些初始向量的系数，标准差σ > 0。从具有小参数的连续高斯分布中采样非常简单，但从离散高斯分布中采样则更难。有几种已知的离散高斯采样方法，包括拒绝采样、反演采样、离散楚格拉特、伯努利型、Knuth-Yao 型和 Von Neumann 型。为了提高效率，我们推荐 Karney 在 [Kar16] 中引入的 Von Neumann 型采样方法。

**Constant-time sampling.** In some of the aforementioned sampling methods, the time it takes to generate one sample could leak information about the actual sample. In many applications, it is therefore important that the entire error-sampling process is constant-time. This is easier to do when sampling from the continuous Gaussian distribution, but harder for the discrete Gaussian. One possible method is to fix some upper bound 𝑇 > 0 such that sampling all the 𝑛 coordinates 𝑒𝑖 sequentially without interruption takes time less than 𝑇 time with overwhelming probability. Then after these samples are generated, using time 𝑡, we wait for (𝑇 − 𝑡) time units, so that the entire error-generating time always takes time 𝑇. In this way, the total time does not reveal information about the generated error polynomial.
在上述一些采样方法中，生成一个样本所需的时间可能会泄露有关实际样本的信息。因此，在许多应用中，整个误差采样过程必须是恒定时间的。当从连续高斯分布中采样时，这更容易做到，但对于离散高斯分布来说更难。一种可能的方法是固定一些上限 T > 0，这样按顺序不间断地采样所有 n 个坐标 ei 所需的时间少于 T 时间，概率极大。然后，在生成这些样本后，使用时间t，我们等待（T−t）时间单位，因此整个错误生成时间总是需要时间T。这样，总时间不会显示有关生成的误差多项式的信息。


## TABLES of RECOMMENDED PARAMETERS
In practice, in order to implement homomorphic encryption for a particular application or task, the application will have to select a dimension 𝑛, and a ciphertext modulus 𝑞, (along with a plaintext modulus and a choice of encoding which are not discussed here). For that reason, we give pairs of (𝑛, 𝑞)which achieve different security levels for each 𝑛. In other words, given 𝑛, the table below recommends a value of 𝑞 which will achieve a given level of security (e.g. 128 bits) for the given error standard deviation 𝜎 ≈ 3.2. 
在实践中，为了实现特定应用程序或任务的同态加密，应用程序必须选择维度 n 和密文模数 q（以及明文模数和编码选择，此处不讨论）。出于这个原因，我们给出了 （n， q） 对，它们对每个 n 实现了不同的安全级别。换言之，给定 n，下表建议的值为 q，该值将达到给定的安全级别（例如 128 位），给定误差标准差 σ ≈ 3.2。

We have the following tables for 3 different security levels, 128-bit, 192-bit, and 256-bit security, where the secret follows the uniform, error, and ternary distributions. For applications, we give values of 𝑛from 𝑛 = 2𝑘 where 𝑘 = 10, … ,15. We note that we used commit (560525) of the LWE-estimator of [APS15], which the authors continue to develop and improve. The tables give estimated running times (in bits) for the three attacks described in Section 5.1: uSVP, dec (decoding attack), and dual.
下表列出了 3 个不同的安全级别，即 128 位、192 位和 256 位安全级别，其中密钥遵循统一分布、错误分布和三元分布。对于应用程序，我们给出 nfrom n = 2k 的值，其中 k = 10， ... ，15。我们注意到，我们使用了 [APS15] 的 LWE 估计器的提交 （560525），作者继续开发和改进它。这些表给出了第 5.1 节中描述的三种攻击的估计运行时间（以位为单位）：uSVP、dec（解码攻击）和双重攻击。


### Table 1: Cost model = BKZ.sieve
distribution | n | security <br> level | logq | uSVP | dec | dual
| --- | ---: | ---: | ---: | ---: | ---: | ---: |
uniform | 1024 | 128 | 29 | 131.2 | 145.9 | 161.0
&nbsp;|&nbsp;| 192 | 21 | 192.5 | 225.3 | 247.2
&nbsp;|&nbsp;| 256 | 16| 265.8 | 332.6 | 356.7
&nbsp;|2048 | 128 | 56 | 129.8 | 137.9 | 148.2
&nbsp;|&nbsp;|192 | 39 | 197.6 | 217.5 | 233.7
&nbsp;|&nbsp;|256 | 31 | 258.6 | 294.3 | 314.5
&nbsp;|4096 | 128 | 111 | 128.2 | 132.0 | 139.5
&nbsp;|&nbsp;|192 | 77 | 194.7 | 205.5 | 216.4
&nbsp;|&nbsp;|256 | 60 | 260.4 | 280.4 | 295.1
&nbsp;|8192 | 128 | 220 | 128.5 | 130.1 | 136.3
&nbsp;|&nbsp;|192 | 154 | 192.2 | 197.5 | 205.3
&nbsp;|&nbsp;|256 | 120 | 256.5 | 267.3 | 277.5
&nbsp;|16384 | 128 | 440 | 128.1 | 129.0 | 133.9
&nbsp;|&nbsp;|192 | 307 | 192.1 | 194.7 | 201.0
&nbsp;|&nbsp;|256 | 239 | 256.6 | 261.6 | 269.3
&nbsp;|32768 | 128 | 880 | 128.8 | 129.1 | 133.6
&nbsp;|&nbsp;|192 | 612 | 193.0 | 193.9 | 198.2
&nbsp;|&nbsp;|256 | 478 | 256.4 | 258.8 | 265.1
error | 1024 | 128 | 29 | 131.2 | 145.9 | 141.8
&nbsp;|&nbsp;|192 | 21 | 192.5 | 225.3 | 210.2
&nbsp;|&nbsp;|256 | 16 | 265.8 | 332.6 | 300.5
&nbsp;|2048 | 128 | 56 | 129.8 | 137.9 | 135.7
&nbsp;|&nbsp;|192 | 39 | 197.6 | 217.5 | 209.6
&nbsp;|&nbsp;|256 | 31 | 258.6 | 294.3 | 280.3
&nbsp;|4096 | 128 | 111 | 128.2 | 132.0 | 131.4
&nbsp;|&nbsp;|192 | 77 | 194.7 | 205.5 | 201.5
&nbsp;|&nbsp;|256 | 60 | 260.4 | 280.4 | 270.1
&nbsp;|8192 | 128 | 220 | 128.5 | 130.1 | 130.1
&nbsp;|&nbsp;|192 | 154 | 192.2 | 197.5 | 196.9
&nbsp;|&nbsp;|256 | 120 | 256.5 | 267.3 | 263.8
&nbsp;|16384 | 128 | 440 | 128.1 | 129.3 | 130.2
&nbsp;|&nbsp;|192 | 307 | 192.1 | 194.7 | 196.2
&nbsp;|&nbsp;|256 | 239 | 256.6 | 261.6 | 264.5
&nbsp;|32768 | 128 | 883 | 128.5 | 128.8 | 130.0
&nbsp;|&nbsp;|192 | 613 | 192.7 | 193.6 | 193.4
&nbsp;|&nbsp;|256 | 478 | 256.4 | 258.8 | 257.9
(-1, 1) | 1024 | 128 | 27 | 131.6 | 160.2 | 138.7
&nbsp;|&nbsp;|192 | 19 | 193.0 | 259.5 | 207.7
&nbsp;|&nbsp;|256 | 14 | 265.6 | 406.4 | 293.8
&nbsp;|2048 | 128 | 54 | 129.7 | 144.4 | 134.2
&nbsp;|&nbsp;|192|  37 | 197.5 | 233.0 | 207.8
&nbsp;|&nbsp;|256 | 29 | 259.1 | 321.7 | 273.5
&nbsp;|4096 | 128 | 109 | 128.1 | 134.9 | 129.9
&nbsp;|&nbsp;|192 | 75 | 194.7 | 212.2 | 198.5
&nbsp;|&nbsp;|256 | 58 | 260.4 | 292.6|  270.1
&nbsp;|8192 | 128 | 218 | 128.5 | 131.5 | 129.2
&nbsp;|&nbsp;|192 | 152 | 192.2 | 200.4 | 194.6
&nbsp;|&nbsp;|256 | 118 | 256.7 | 273.0 | 260.6
&nbsp;|16384 | 128 | 438 | 128.1 | 129.9 | 129.0
&nbsp;|&nbsp;|192 | 305 | 192.1 | 196.2 | 193.2
&nbsp;|&nbsp;|256 | 237 | 256.9 | 264.2 | 259.8
&nbsp;|32768 | 128 | 881 | 128.5 | 129.1 | 128.5
&nbsp;|&nbsp;|192 | 611 | 192.7 | 194.2 | 193.7
&nbsp;|&nbsp;|256 | 476 | 256.4 | 260.2 | 258.2

**Post-quantum security.** The BKZ.qsieve model assumes access to a quantum computer and gives lower estimates than BKZ.sieve. In what follows, we give tables of recommended (“Post-quantum”) parameters which achieve the desired levels of security against a quantum computer. We also present tables computed using the ``quantum” mode of the BKZ.ADPS16 model, which contain more conservative parameters. 
**后量子安全性。 BKZ.qsieve 模型假定可以访问量子计算机，并且给出的估计值低于 BKZ.sieve。在下文中，我们给出了推荐的（“后量子”）参数表，这些参数实现了针对量子计算机的所需安全级别。我们还展示了使用 BKZ 的“量子”模式计算的表。ADPS16 模型，其中包含更保守的参数。


### Table 2: Cost model = BKZ.qsieve
distribution | n | security <br> level | logq | uSVP | dec | dual
| --- | ---: | ---: | ---: | ---: | ---: | ---: |
uniform | 1024 | 128 | 27 | 132.2 | 149.3 | 164.5
&nbsp;|&nbsp;|192 | 19 | 199.3 | 241.6 | 261.6
&nbsp;|&nbsp;|256 | 15 | 262.9 | 341.1 | 360.8
&nbsp;|2048 | 128 | 53 | 128.1 | 137.6 | 147.6
&nbsp;|&nbsp;|192 | 37 | 193.6 | 215.8 | 231.4
&nbsp;|&nbsp;|256 | 29 | 257.2 | 297.9 | 316.6
&nbsp;|4096 | 128 | 103 | 129.1 | 134.2 | 141.7
&nbsp;|&nbsp;|192 | 72 | 193.8 | 206.2 | 217.2
&nbsp;|&nbsp;|256 | 56 | 259.2|  281.9 | 296.5
&nbsp;|8192 | 128 | 206 | 128.2 | 130.7 | 136.6
&nbsp;|&nbsp;|192 | 143 | 192.9 | 199.3 | 207.3
&nbsp;|&nbsp;|256 | 111 | 258.4 | 270.8 | 280.7
&nbsp;|16384 | 128 | 413 | 128.2 | 129.0 | 132.7
&nbsp;|&nbsp;|192 | 286 | 192.1 | 195.3 | 201.4
&nbsp;|&nbsp;|256 | 222 | 257.2 | 263.1 | 270.6
&nbsp;|32768 | 128 | 829 | 128.1 | 128.4 | 130.8
&nbsp;|&nbsp;|192 | 573 | 192.0 | 193.3 | 197.5
&nbsp;|&nbsp;|256 | 445 | 256.1 | 259.0 | 265.2
error | 1024 | 128 | 27 | 132.2 | 149.3 | 144.5
&nbsp;|&nbsp;|192 | 19 | 199.3 | 241.6 | 224.0
&nbsp;|&nbsp;|256 | 15 | 262.9 | 341.1 | 302.3
&nbsp;|2048 | 128 | 53 | 128.1 | 137.6 | 134.8
&nbsp;|&nbsp;|192 | 37 | 193.6 | 215.8 | 206.7
&nbsp;|&nbsp;|256 | 29 | 257.2 | 297.9 | 281.4
&nbsp;|4096 | 128 | 103 | 129.1 | 134.2 | 133.1
&nbsp;|&nbsp;|192 | 72 | 193.8 | 206.2 | 201.8
&nbsp;|&nbsp;|256 | 56 | 259.2 | 281.9 | 270.4
&nbsp;|8192 | 128 | 206 | 128.2 | 130.7 | 130.1
&nbsp;|&nbsp;|192 | 143 | 192.9 | 199.3 | 198.5
&nbsp;|&nbsp;|256 | 111 | 258.4 | 270.8 | 266.6
&nbsp;|16384 | 128 | 413 | 128.2 | 129.0 | 130.1
&nbsp;|&nbsp;|192 | 286 | 192.1 | 195.3 | 196.6
&nbsp;|&nbsp;|256 | 222 | 257.2 | 263.1 | 265.8
&nbsp;|32768 | 128 | 829 | 128.1 | 128.4 | 129.8
&nbsp;|&nbsp;|192 | 573 | 192.0 | 193.3 | 192.8
&nbsp;|&nbsp;|256 | 445 | 256.1 | 259.0 | 260.4
(-1, 1) | 1024 | 128 | 25 | 132.6 | 165.5 | 142.3
&nbsp;|&nbsp;|192 | 17 | 199.9 | 284.1 | 222.2
&nbsp;|&nbsp;|256 | 13 | 262.6 | 423.1 | 296.6
&nbsp;|2048 | 128 | 51 | 128.6 | 144.3 | 133.4
&nbsp;|&nbsp;|192 | 35 | 193.5 | 231.9 | 205.2
&nbsp;|&nbsp;|256 | 27 | 257.1 | 327.8 | 274.4
&nbsp;|4096 | 128 | 101 | 129.6 | 137.4 | 131.5
&nbsp;|&nbsp;|192 | 70 | 193.7|  213.6 | 198.8
&nbsp;|&nbsp;|256 | 54 | 259.7 | 295.2 | 270.6
&nbsp;|8192 | 128 | 202 | 129.8 | 130.7 | 128.0
&nbsp;|&nbsp;|192 | 141 | 192.9 | 202.5 | 196.1
&nbsp;|&nbsp;|256 | 109 | 258.3 | 276.6 | 263.1
&nbsp;|16384 | 128 | 411 | 128.2 | 129.5 | 129.0
&nbsp;|&nbsp;|192 | 284 | 192.0 | 196.8 | 193.7
&nbsp;|&nbsp;|256 | 220 | 257.2 | 265.8 | 260.7
&nbsp;|32768 | 128 | 827 | 128.1 | 128.7 | 128.4
&nbsp;|&nbsp;|192 | 571 | 192.0 | 194.1 | 193.1
&nbsp;|&nbsp;|256 | 443 | 256.1 | 260.4 | 260.4


## Appendix A

Organizers
Name | Email
|---|---|
Kristin Lauter | klauter@microsoft.com
Vinod Vaikuntanathan |vinod.nathan@gmail.com

Contributors

Name | Email
|---|---|
Martin Albrecht | martinralbrecht@googlemail.com
Melissa Chase | melissac@microsoft.com
Hao Chen | haoche@microsoft.com
Jintai Ding | jintai.ding@gmail.com
Shafi Goldwasser | shafi@theory.csail.mit.edu
Sergey Gorbunov | sgorbunov100@gmail.com
Shai Halevi | shaih@alum.mit.edu
Jeffrey Hoffstein | hoffsteinjeffrey@gmail.com
Satya Lokam | Satya.Lokam@microsoft.com
Daniele Micciancio | daniele@cs.ucsd.edu
Dustin Moody | dustin.moody@nist.gov
Travis Morrison | txm950@psu.edu
Amit Sahai | amitsahai@gmail.com

## References
[Alb17] Albrecht, M. R. (2017). On dual lattice attacks against small-secret LWE and parameter choices in HElib and SEAL. In J. Coron & J. B. Nielsen (Eds.), EUROCRYPT 2017, part ii (Vol. 10211, pp. 103–129). Springer, Heidelberg.
[AFG14] Martin R. Albrecht, Robert Fitzpatrick, and Florian Gopfert: On the Efficacy of Solving LWE by Reduction to Unique-SVP. In Hyang-Sook Lee and Dong-Guk Han, editors, ICISC 13, volume 8565 of LNCS, pages 293-310. Springer, November 2014. 
[AGVW17] Albrecht, M. R., Göpfert, F., Virdia, F., & Wunderer, T. (2017). Revisiting the expected cost of solving uSVP and applications to LWE. In T. Takagi & T. Peyrin (Eds.), ASIACRYPT 2017, part i (Vol. 10624, pp. 297–322). Springer, Heidelberg.
[APS15] Martin R. Albrecht, Rachel Player and Sam Scott. On the concrete hardness of Learning with Errors. Journal of Mathematical Cryptology. Volume 9, Issue 3, Pages 169–203, ISSN (Online) 1862-2984, October 2015.
[ADPS16] Alkim, E., Ducas, L., Pöppelmann, T., & Schwabe, P. (2016). Post-quantum key exchange - A new hope. In T. Holz & S. Savage (Eds.), 25th USENIX security symposium, USENIX security 16 (pp. 327–343). USENIX Association. Retrieved from https://www.usenix.org/conference/usenixsecurity16/technical-sessions/presentation/alkim
[AP14] Alperin-Sheriff, J., Peikert, C.: Faster bootstrapping with polynomial error. In: Garay, J.A., Gennaro, R. (eds.) CRYPTO 2014. LNCS, vol. 8616, pp. 297–314. 
[AG11] Sanjeev Arora and Rong Ge. New algorithms for learning in the presence of errors. In ICALP, volume 6755 of Lecture Notes in Computer Science, pages 403–415. Springer, 2011.
[Bab86] László Babai: On Lovász’ lattice reduction and the nearest lattice point problem, Combinatorica, 6(1):1-3, 1986. 
[BDGL16] Becker, A., Ducas, L., Gama, N., & Laarhoven, T. (2016). New directions in nearest neighbor searching with applications to lattice sieving. In R. Krauthgamer (Ed.), 27th soda (pp. 10–24). ACM-SIAM. https://doi.org/10.1137/1.9781611974331.ch2
[BGV12]: Zvika Brakerski, Craig Gentry, Vinod Vaikuntanathan. (Leveled) fully homomorphic encryption without bootstrapping. In ITCS '12 Proceedings of the 3rd Innovations in Theoretical Computer Science Conference. Pages 309-325.
[B12] Zvika Brakerski. Fully Homomorphic Encryption without Modulus Switching from Classical GapSVP, In CRYPTO 2012. Pages 868 – 886. 
[CIV16a] W. Castryck, I. Iliashenko, F. Vercauteren, Provably weak instances of ring-lwe revisited. In: Eurocrypt 2016. vol. 9665, pp. 147–167. Springer (2016)
[CIV16b] W. Castryck, I. Iliashenko, F. Vercauteren, On error distributions in ring-based LWE. LMS Journal of Computation and Mathematics 19(A), 130–145 (2016) 7. [Che13 ] Chen, Y. (2013). Réduction de réseau et sécurité concrète du chiffrement complètement homomorphe (PhD thesis). Paris 7.
[CKKS17] Jung Hee Cheon, Andrey Kim, Miran Kim, Yongsoo Song. Homomorphic encryption for arithmetic of approximate numbers, In International Conference on the Theory and Applications of Cryptology and Information Security, pp. 409–437. Springer, Cham. 2017.
[CLS15] Hao Chen, Kristin Lauter, Katherine E. Stange, Attacks on the Search RLWE Problem with Small Errors, SIAM J. Appl. Algebra Geometry, Society for Industrial and Applied Mathematics, Vol. 1, pp. 665–682. (2017) https://eprint.iacr.org/2015/971
[CLS16] Hao Chen, Kristin Lauter, Katherine E. Stange. Security Considerations for Galois Non-dual RLWE Families, SAC 2016: Selected Areas in Cryptography – SAC 2016 Lecture Notes in Computer Science, Vol. 10532. Springer pp 443-462. 
[CN11] Y. Chen, P.Q. Nguyen. BKZ 2.0: Better Lattice Security Estimates. In: Lee D.H., Wang X. (eds) Advances in Cryptology – ASIACRYPT 2011. ASIACRYPT 2011. Lecture Notes in Computer Science, vol.7073. Springer, Berlin, Heidelberg.
[CGGI16] Chillotti, I., Gama, N., Georgieva, M., Izabachène, M.: Faster fully homomorphic encryption: bootstrapping in less than 0.1 seconds. In: Cheon, J.H., Takagi, T. (eds.) ASIACRYPT 2016. LNCS, vol. 10031, pp. 3–33.
[CS16] Ana Costache, Nigel P. Smart, Which Ring Based Somewhat Homomorphic Encryption Scheme is Best? Topics in Cryptology - CT-RSA 2016, LNCS, volume 9610, Pages 325-340.
[CP16] Eric Crockett and Chris Peikert. Λ∘λ: Functional Lattice Cryptography. In ACM-CCS 2016.
[DM15] Ducas, L., Micciancio, D.: FHEW: bootstrapping homomorphic encryption in less than a second. In: Oswald, E., Fischlin, M. (eds.) EUROCRYPT 2015. LNCS, vol. 9056, pp. 617–640.
[ELOS15] Yara Elias, Kristin Lauter, Ekin Ozman, Katherine E. Stange, Provably weak instances of Ring￾LWE, CRYPTO 2015
[FV12] J. Fan and F. Vercauteren. Somewhat practical fully homomorphic encryption. Cryptology ePrint Archive, Report 2012/144, 2012. http://eprint.iacr.org/2012/144.pdf
[GINX16] Gama, N., Izabachène, M., Nguyen, P.Q., Xie, X.: Structural lattice reduction: generalized worst￾case to average-case reductions. In: EUROCRYPT 2016, https://eprint.iacr.org/2014/283.pdf
[GSW] C. Gentry, A. Sahai, and B. Waters. Homomorphic Encryption from Learning with Errors: 
Conceptually-Simpler, Asymptotically-Faster, Attribute-Based. In CRYPTO 2013 (Springer).
[Kar16] C.F.F. Karney, Sampling Exactly from the Normal Distribution. ACM Transactions on Mathematical Software, 42, Article No. 3. 
[KL15] Miran Kim and Kristin Lauter, Private Genome Analysis through Homomorphic Encryption,BioMedCentral Journal of Medical Informatics and Decision Making 2015 15 (Suppl 5): S3.
[LL15] Kim Laine and Kristin Lauter, Key Recovery for LWE in Polynomial Time. https://eprint.iacr.org/2015/176
[Laa15] Laarhoven, T. (2015). Search problems in cryptography: From fingerprinting to lattice sieving(PhD thesis). Eindhoven University of Technology.
[LMvP13] Laarhoven T., Mosca M., van de Pol J. (2013) Solving the Shortest Vector Problem in Lattices Faster Using Quantum Search. In: Gaborit P. (eds) Post-Quantum Cryptography. PQCrypto 2013. Lecture Notes in Computer Science, vol 7932. Springer, Berlin, Heidelberg.
[LP11] Richard Lindner and Chris Peikert: Better key sizes (and attacks) for LWE-based encryption. In Topics in Cryptology - CT-RSA 2011 - The Cryptographers' Track at the RSA Conference 2011, Aggelos Kiayias, Editor, volume 6558 of LNCS, pages 319—339. 
[LN13] Liu, M., & Nguyen, P. Q. (2013). Solving BDD by enumeration: An update. In E. Dawson (Ed.), CT￾rsa 2013 (Vol. 7779, pp. 293–309). Springer,Heidelberg. https://doi.org/10.1007/978-3-642-36095-4_19
[LTV12] A. Lopez-Alt, E. Tromer, and V. Vaikuntanathan. On-the-fly multiparty computation on the cloud via multikey fully homomorphic encryption. In STOC, pages 1219–1234, 2012. 
[LPR13] Vadim Lyubashevsky, Chris Peikert, and Oded Regev : On Ideal Lattices and Learning with Errors over Rings. Journal of the ACM (JACM), Volume 60, Issue 6, November 2013, Article No. 43. 
[LPR13b] Vadim Lyubashevsky, Chris Peikert, and Oded Regev : A toolkit for ring-LWE cryptography. Annual International Conference on the Theory and Applications of Cryptographic Techniques. Springer, Berlin, Heidelberg, 2013.
[MR09] Micciancio, D., & Regev, O. (2009). Lattice-based cryptography. In D. J. Bernstein, J. Buchmann, & E. Dahmen (Eds.), Post-quantum cryptography (pp. 147–191). Berlin, Heidelberg, New York: Springer, Heidelberg.
[HPS98] J. Hoffstein, J. Pipher, and J. H. Silverman. NTRU: A ring-based public key cryptosystem. In J. Buhler, editor, ANTS, volume 1423 of Lecture Notes in Computer Science, pages 267–288. Springer, 1998.
[P16] C. Peikert, How Not to Instantiate Ring-LWE, in SCN’16, volume 9841 of LNCS, Springer, 2016.
[YASHE13] Joppe W. Bos, Kristin Lauter, Jake Loftus, and Michael Naehrig. Improved Security for a Ring-Based Fully Homomorphic Encryption Scheme, in IMA CC 2013. http://eprint.iacr.org/2013/075.pdf


Software references for publicly available Homomorphic Encryption libraries:
[cuFHE] https://github.com/vernamlab/cuFHE
[cuHE] https://github.com/vernamlab/cuHE
[HEAAN] https://github.com/snucrypto/HEAAN
[HElib] https://github.com/shaih/HElib
[NFLlib] https://github.com/CryptoExperts/FV-NFLlib
[PALISADE] https://git.njit.edu/groups/PALISADE
[SEAL] http://sealcrypto.org
[TFHE] https://tfhe.github.io/tfhe/


## Homomorphic Encryption Standard Appendix Anticipated Extensions to this Document
This document is only a first step in standardizing various aspects of homomorphic encryption, and we expect many other aspects to be standardized in future documents. Some aspects that were not specified here and we expect to be specified in future versions include the following:
- The homomorphic encryption scheme for approximate numbers by Cheon, Kim, Kim and Song[CKKS17], which is mentioned in Section 1.1.5.
- Homomorphic encryption based on Module LWE, mentioned in Section 2.1.1.
- Concrete parameters and sampling methods for non-power-of-two cyclotomic rings, as discussed in Section 2.1.3.
- Parameter choices when using sparse secret key, as mentioned in Section 2.1.3.
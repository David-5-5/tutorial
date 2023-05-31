[TOC]


# 四、结构型模式
结构型模式涉及到如何组合类和对象以获得更大的结构。

- 结构型类模式
  采用继承机制来组合接口或实现，这一模式尤其有助于多个独立开的类库协同工作
- 结构型对象模式
  不是对接口和实现进行组合，而是描述了如何对一些对象进行组合，从而实现新功能的一些方法
  因为可以在运行时刻改变对象的组合关系，所以对象组合模式具有更大的灵活性。而这种机制用静态类组合是不可能实现的

> 思考：**体会两种模式的差异**
除了Adapter适配器模式是类对象结构型模式，其他Bridge桥接模式、Composite组成模式都是对象结构型模式。


## 4.1 <span id="4.1">ADAPTER 适配器</span>

类型：类对象结构型模式

### 4.1.1 <span id="4.1.1">定义及类图</span>

将一个类的接口转化为客户希望的另外一个接口。使得原本由于接口不兼容的而不能一起工作的类可以一起工作。也成为包装器Wrapper。

Adapter 适配器的通用UML类图如下：

- 类适配器使用多重继承对一个接口与另一个接口进行匹配
```mermaid
classDiagram

class Target {
    request()
}

class Adaptee {
    specificRequest()
}

class Adapter {
    request
}

Client ..> Target : 依赖

Target <|.. Adapter : 实现
Adaptee <|-- Adapter : 继承

```
Adapter的实现specificRequest方法

- 对象匹配器依赖于对象组合
```mermaid
classDiagram

class Target {
    request()
}

class Adaptee {
    specificRequest()
}

class Adapter {
    request
}

Client ..> Target : 依赖

Target <|.. Adapter : 实现
Adaptee <.. Adapter : 依赖

Adaptee<|-- AdapteeChild1 : 继承
Adaptee<|-- AdapteeChildN : 继承

```
Adapter的调用adaptee.specificRequest方法


上述类图说明如下：
- Target，定义Client使用的特定领域相关的接口
- Client，与符合Target接口的对象协同
- Adaptee，定义一个已经存在的接口，这个接口需要适配
- Adapter，对Adpatee的接口与Target接口进行适配

Client在Adapter实现上调用一些操作，接着适配器调用Adaptee的操作实现这个请求

Adapter模式可以使用类适配器和对象适配器两种类型（比较上述两个类图结构），需要根据情况进行权衡
- 使用类适配器
  - 用一个具体的Adapter类对Adaptee和Target进行匹配。<font color="Red">*结果是当想要匹配一个类及所有它的子类是，类Adapter将不能胜任*</font>
  - 使得Adapter可以重定义Adaptee的部分行为，因为Adapter是Adaptee的一个子类
  - 仅仅引入一个对象，不需要额外的指针以间接得到Adaptee
  - **补充**对于类似Java不支持多重继承的语言，Target应定义为一个接口，而Adaptee可以是一个类
- 使用对象适配器
  - 允许Adapter与多个Adaptee，即Adaptee本身及其它的所有子类同时工作。Adaptee可以一次给所有的Adaptee添加功能
  - <font color="Red">*使得重定义Adaptee的行为比较困难。*</font>这就需要生成Adaptee的子类并且使得Adapter因为子类而不是Adaptee本身


使用Adapter模式需要考虑的一些其他因素有：
1. Adatper的匹配程度
2. 可插入的Adatper
3. 使用双向适配器提供透明操作


实现Adapter模式，需要注意的一些问题：
1. 使用C++实现适配器类
2. 可插入的适配器
   - 使用抽象操作
   - 使用代理对象
   - 参数化的适配器


### 4.1.2 <span id="4.1.2">应用场景</span>

适用的场景包括：
- 需要要使用一个已经存在的类，而它的接口不符合你的需求
- 需要创建一个可以复用的类，该类可以与其他不相干的类或不可预见的类协同工作
- 需要使用一些已经存在的类，但是不可能对每一个都进行子类化以匹配他们的接口。对象适配器可以适配它的父类接口


### 4.1.2.1 <span id="4.1.2.1">MyBatis</span>


### 4.1.2.2 <span id="4.1.2.2">JDK</span>

InputStreamReader(InputStream in)构造函数，返回Reader接口的实现类

```mermaid
classDiagram


class InputStreamReader {
  private StreamDecoder sd
  InpuStreamReader(InputStream in)
}

Reader <|.. InputStreamReader : 实现
Reader <|.. StreamDecoder : 实现

InputStream <.. StreamDecoder : 依赖
StreamDecoder <.. InputStreamReader : 依赖


```
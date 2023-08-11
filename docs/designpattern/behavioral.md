[TOC]


# 五、行为模式
行为模式涉及到算法和对象间职责的分配。行为模式不仅描述对象或类的模式，还描述它们之间的通信模式。

- 行为类模式使用继承机制在类间分派行为
- 行为对象模式使用对象复合而不是继承



## 5.1 <span id="5.1">CHAIN OF RESPONSIBILITY职责链</span>

类型：对象行为型模式

### 5.1.1 <span id="5.1.1">定义及类图</span>

使多个对象都有机会处理请求，从而避免请求的发送者和接受者之间的耦合关系。将这些对象连成一条链，并沿着这条链传递该请求，直到有一个对象处理它为止。

这一模式的想法是，给多个对象处理一个请求的机会，从而解耦发送者和接收者。该请求沿着对象链传递直至其中一个对象处理它。

Adapter 适配器的通用UML类图如下：

- 类适配器使用多重继承对一个接口与另一个接口进行匹配
```mermaid
classDiagram

class Handler {
    handleRequest()
}

class ConcreteHandler1 {
    handleRequest()
}

class ConcreteHandler2 {
    handleRequest()
}

Handler <|.. ConcreteHandler1 : 实现
Handler <|.. ConcreteHandler2 : 实现


Client ..> Handler : 依赖 Dependency
Handler ..> Handler : successor

```
上述类图说明如下：
- Handler，定义一个处理请求的接口，(可选)并实现后续链
- ConcreteHandler
  - 处理它所负责的请求
  - 可访问它的后续者
  - 如果可处理该请求，则处理；否则将该请求转发给它的后续者
- Client，向链上的具体处理者对象提交请求

一个典型的对象结构可能如下图所示：

```mermaid
graph LR

id1([aClient\naHandler])
id2([aHandler\nsuccessor])
id3([aHandler\nsuccessor])

id1 --> id2
id2 --> id3

```


当客户提交一个请求时，请求沿着责任链传递直至有一个ConcreteHandler对象负责处理它。


优缺点分析：
- (Adv) 降低耦合度。该模式使得一个对象无需知道是其他哪一个对象处理其请求。
  - 对象仅需知道该请求会被"正确"的处理
  - 接收者和发送者都没有对方的明确信息，且链中的对象不需要知道链的结构
  - 结果是责任链可简化为对象的相互连接。它们仅需保持一个指向其后续者的引用，而不需要保持它所有候选后续者的引用。
- (Adv) 增强了个对象指派职责的灵活性
  - 通过在运行时对该链进行动态的增加或修改来增加或改变处理一个请求的那些职责。
  - 将这种机制与静态的特例化处理对象的继承机制结合起来使用
- (Disadv) 不保证被接受，既然一个请求没有明确的接受者，那么就不能保证它一定会被处理
  - 请求可能一直到链的末端都得不到处理
  - 请求也可能因没有被正确配置而得不到处理


责任链的实现问题：
1. 实现后续者链的两种方法：
  - 定义新的链接，通常在Handler中定义，但也可由ConcreteHandler来定义
  - 使用已有的链接。
    - 使用已有的对象引用来形成后续者链。
    - 当已有的链接能支持所需的链时，完全可以使用它们。
2. 连接后续者，如果没有已有的引用可定义一个链，必须自行引入它们。这种情况下Handler不仅定义该请求的接口，通常也维护后续链接。

```C++
class HelpHandler {
public:
    HelpHandler(HelpHandler* s) : _successor(s) { }
    virtual void HandleHelp();
private:
    HelpHandler* _successor;
};

void HelpHandler::HandleHelp () {
    if (_successor) {
        _successor->HandleHelp();
    }
}
```
上述代码`HelpHandler(HelpHandler* s) : _successor(s) { }`为C++构造函数的初始化成员列表用法
> 成员初始化表达式列表
构造函数可以选择具有成员初始化表达式列表，该列表会在构造函数主体运行之前初始化类成员。 （成员初始化表达式列表与类型为 std::initializer_list<T> 的初始化表达式列表不同。）
首选成员初始化表达式列表，而不是在构造函数主体中赋值。 成员初始化表达式列表直接初始化成员。 以下示例演示了成员初始化表达式列表，该列表由冒号后的所有 identifier(argument) 表达式组成：
```C++
Box(int width, int length, int height)
        : m_width(width), m_length(length), m_height(height)
    {}
```

为便于理解，将上述C++转换为Java语言如下
```Java
public class HelpHandler {
    private HelpHandler _successor;

    public HelpHandler(HelpHandler s) {
        _successor = s;
    }

    public void HandleHelp() {
        if (_successor != null) {
            _successor.HandleHelp();
        }
    }
}

```

3. 表示请求



### 5.1.2 <span id="5.1.2">应用场景</span>

适用的场景包括：
- 有多个的对象可以处理一个请求，哪个对象处理该请求运行时刻自动确定
- 不明确指定接受者的情况下，向多个对象中的一个提交一个请求
- 可处理一个请求的对象集合应被动态指定


#### 5.1.2.1 <span id="5.1.2.1">Commons-chain</span>

Chain将Template Method模版方法和Chain of Responsibility责任链两个模式组合成一个可复用的Java框架用于描述顺序的处理流程。

Commons Chain的类和接口
```mermaid
classDiagram

class Command {
    boolean execute(Context cnt)
}

class Chain {
    void addCommand(Command cmd)
    boolean execute(Context cnt)
}

class ChainBase {
    void addCommand(Command cmd)
    boolean execute(Context cnt)
    Command[] getCommands()
}

class Filter {
    boolean execute(Context cnt)
    boolean postprocess(Context cnt, Exception ex)
}


Command --o Chain : 聚合 Aggregation
Command <|-- Filter : 继承

Chain <|.. ChainBase : 实现

Context <|.. ContextBase : 实现

Command ..> Context : 依赖 Dependency

```
Command 类和Chain类的关系就是组合模式（Composite pattern）。Chain不仅由多个Command组成，而且自己也是Command。这使你可以非常简单得将单个命令（Command）替换成由多个命令（Command）组成的链（Chain）。
- Command: 一个可执行的"指令"，多个command组成"责任链"。
  - 它只有一个方法，boolean execute(Context context)，当"责任链"开始调用时，将会依次执行链上的所有Command对象execute方法，直到结束，或者抛出异常，或者某个command返回true终止调用。context对象表示当前"责任链"的上下文信息，它可以用来保存一些临时变量(可以在command间共享)。
  - 此方法如果返回false，表示继续责任链将会继续执行后续command，
  - 如果返回true，则表示终止调用，后续的command将不会被执行.
- Chain：实现类为ChainBase，command组织者，包括addCommand方法，可以添加多个command，再通过调用execute方法，会依次执行command链中的execute方法。
- Filter：它本身也扩展了Command接口,能够和Command一样添加到Chain中。
  - 当所有command以及filter的execute方法都执行完毕且没有异常，那么将会对Filter的postprocess方法按倒序执行；
  - 一旦链路发生异常，将立即执行filter的postprocess方法，如果方法处理完后返回true，表示错误处理已经完成，链的执行并不会就此结束，但是本质上来说这个错误被捕捉而且不会再向外抛出。
  - 如果postprocess方法返回false，那错误会继续向外抛出，然后链就会非正常结束。
- Context：类似于"session"，用来保存当前Chain中需要被保持的"变量参数"或者"Command执行的结果"，Context内部存储结构为一个Map，它的数据可以被Chain中的Command操作，Context并非为线程安全的，也不期望此实例能够被重用，每次Chain被调用，都应该创建新的Context实例，其实现类为ContextBase。



#### 5.1.2.2 <span id="5.1.2.2">Servlet Filters</span>

Java Servlet 规范 2.3 版引入了一种新的组件类型，称为`Filter`。`Filter`动态截获请求和响应，以转换或使用请求或响应中包含的信息。`Filter`本身通常不会创建响应，而是提供可以“附加”到任何类型的 servlet 或 JSP 页面的通用函数。

`Filter`很重要
- 首先，它们提供了将重复性任务封装在可重用单元中的能力。有组织的开发人员一直在寻找模块化代码的方法。模块化代码更易于管理和记录，更易于调试，如果做得好，可以在另一个设置中重用。
- 其次，过滤器可用于转换来自 servlet 或 JSP 页面的响应。Web 应用程序的一个常见任务是格式化发送回客户端的数据。客户端越来越多地需要格式（例如，WML），而不仅仅是 HTML。为了适应这些客户端，在功能齐全的 Web 应用程序中通常有一个强大的转换或筛选组件。

过滤器可以执行许多不同类型的功能，包括但不限于以下功能：

- 基于用户身份的身份验证阻止请求。
- Logging and auditing记录和审核 - 跟踪 Web 应用程序的用户。
- Image conversion图像转换-缩放地图等。
- Data compression数据压缩-缩小下载量。
- Localization-将请求和响应定位到特定区域设置。
- XML 内容的 XSL/T 转换将 Web 应用程序响应定位到多种类型的客户端。

单个`Filter`实例接收servlet请求和响应，FilterChain实例表示整个`Filter`链。然后，每个`Filter`都应该执行其工作，然后终止链，或者调用`chain.doFilter()`将控制权传递给下一个过滤器。


`Filter`接口中最重要的方法是`doFilter`方法，它是`Filter`的核心。此方法通常执行以下一些操作：

- 检查请求标头
- 如果请求对象希望修改请求标头或数据或完全阻止请求，则自定义该请求对象
- 如果响应对象希望修改响应标头或数据，则对其进行自定义
- 调用筛选器链中的下一个实体。如果当前`Filter`是链中以目标servlet结束的最后一个过滤器，那么下一个实体就是链末端的资源；否则，它就是WAR中配置的下一个`Filter`。它通过调用链对象上的`doFilter`方法来调用下一个实体（传入调用它的请求和响应，或者它可能创建的包装版本）。或者，它可以选择通过不调用下一个实体来阻止请求。在后一种情况下，`Filter`负责填写响应。
- 在调用链中的下一个`Filter`后检查响应标头
- 引发异常以指示处理中的错误


以下是认证过滤器的代码示例：
```Java
public class AuthenticatingFilter implements Filter {
    public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain) 
      throws IOException, ServletException {
        HttpServletRequest httpRequest = (HttpServletRequest) request;
        if (!"MyAuthToken".equals(httpRequest.getHeader("X-Auth-Token")) {
             return;
        }
        chain.doFilter(request, response);
    }
}
```



## 5.2 <span id="5.2">COMMADN 命令</span>

类型：对象行为型模式

### 5.2.1 <span id="5.2.1">定义及类图</span>

将一个请求封装为一个对象，从而使你的可用不同的请求对客户进行参数化链；对请求派对或记录请求日至，以及支持可撤销的操作。

有时向某一个对象提交请求，但并不知道关于被请求的操作或请求的接受者的任何信息。命令模式通过将请求本身变成一个对象来使请求接受者可向指定的应用对象提出请求。
- 这个对象的可被存储并像其他对象一样被传递
- 这一模式的关键是一个抽象的Command类，它定义了一个执行操作的接口。

Command 适配器的通用UML类图如下：

- 类适配器使用多重继承对一个接口与另一个接口进行匹配
```mermaid
classDiagram

class Receivor {
    action()
}

class Command {
    execute()
}

class ConcreteCommand {
    State state
    execute()
}

note for ConcreteCommand "receivo->action()"

Client ..> Receivor : 依赖
Client ..> ConcreteCommand : 依赖

Invoker o-- Command : 组合

Command <|.. ConcreteCommand : 实现
Receivor <.. ConcreteCommand : 依赖

```
上述类图说明如下：
- Command，声明执行操作的接口
- ConcreteCommand
  - 将一个接受者对象绑定于一个动作
  - 调用接受者相应的操作，以实现Execute
- Client， 创建一个具体命令对象并设定它的接受者
- Invoker，要求该命令执行这个请求
- Receivor, 知道如何实施与执行一个请求相关的操作。任何类都可能作为一个接受者。
- 类之间的协作
  - Client创建一个ConcreteCommand对象并指定它的Receivor对象
  - Invoker对象存储该ConcreteCommand对象
  - Invoker对象通过调用Command对象的execute操作来提交一个请求。若该命令是可撤销的，ConcreteCommand就在执行Execute操作之前存储当前状态以用于取消该命令。
  - ConcreteCommand对象对调用它的Receivor的一些操作以执行该请求

下图展示了这些对象之间的交互。它说明了Command是如何将调用者和接受者解耦的
```mermaid
sequenceDiagram

participant aReceivor

aClient ->> aCommand: new Command(aReceivor)
activate aClient
activate aCommand
deactivate aCommand
aClient ->> anInvoker: StoreCommand(aCommand)
activate anInvoker
deactivate anInvoker
deactivate aClient

anInvoker ->> aCommand : execute
activate anInvoker
activate aCommand

aCommand ->> aReceivor : action

activate aReceivor
deactivate aReceivor
deactivate aCommand
deactivate anInvoker

```


### 5.2.2 <span id="5.2.2">应用场景</span>

适用的场景包括：
- 类似于MenuItem对象那样，抽象出待执行的动作以参数化某对象。可使用过程语言中的回调函数表达这种参数化机制
- 在不同的时刻指定、排列和执行请求
  - 一个Command对象可以有一个与初始请求无关的生存期。
  - 如果一个请求的接受者可用一种与地址空间无关的方式表达，那么就可将负责该请求的命令对象传送给另一个不同的进程并在那里实现该请求
- 支持取消操作
  - Commmand的Execute操作可在实施操作前将状态存储起来，在取消操作时这个状态用来消除该操作的影响。
  - Command接口必须添加一个Unexecute操作，该操作取消上一次Execute调用的效果。
  - 执行的命令被存储在一个历史列表中，可通过向后和向前遍历这一列表并分别调用Unexecute和Execute操作来实现重数不限的"Undo"和"Redo"
- 支持修改日志，这样当系统崩溃是，这些修改可以被重做一遍
- 用构建在原语操作上的高层操作构造一个系统。这样一种结构在支持事务的信息系统中很常见


#### 5.2.2.1 <span id="5.2.2.1"></span>






### The Java Profile and Performance Diagnostics Related Articles and Blogs

#### Comparing VisualVM, JMC, and async-profiler
中文 [开源 Java 性能分析器比较：VisualVM、JMC 和 async-profiler](https://www.infoq.cn/article/yO6pjms5izsxK5YrZ036)
英文 [Unleash the Power of Open Source Java Profilers: Comparing VisualVM, JMC, and async-profiler](https://www.infoq.com/articles/open-source-java-profilers/)

> Author: Johannes Bechberger

#### Async-profiler - manual by use cases

[Async-profiler - manual by use cases](https://krzysztofslusarski.github.io/2022/12/12/async-manual.html)


#### hyperfine

[hyperfine](https://github.com/sharkdp/hyperfine) 命令行基准测试工具。

##### 特征
- 跨多次运行的统计分析。
- 支持任意 shell 命令。
- 关于基准进度和当前估计的持续反馈。
- 预热运行可以在实际基准测试之前执行。
- 可以在每次计时运行之前设置缓存清除命令。
- 统计异常值检测，用于检测来自其他程序的干扰和缓存效应。
- 将结果导出为各种格式：CSV、JSON、Markdown、AsciiDoc。
- 参数化基准测试（例如，改变线程数）。
- 跨平台


#### jq
[jq](https://stedolan.github.io/jq) - commandline JSON processor [version 1.6]

```shell
Usage:	jq [options] <jq filter> [file...]
	jq [options] --args <jq filter> [strings...]
	jq [options] --jsonargs <jq filter> [JSON_TEXTS...]
```

jq is a tool for processing JSON inputs, applying the given filter to
its JSON text inputs and producing the filter's results as JSON on
standard output.

The simplest filter is ., which copies jq's input to its output
unmodified (except for formatting, but note that IEEE754 is used
for number representation internally, with all that that implies).

Example:

	$ echo '{"foo": 0}' | jq .
	{
		"foo": 0
	}

For a listing of options, use jq --help.
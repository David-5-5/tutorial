class _RunnerDecorator:
    def __init__(self, meta: "ComponentMeta") -> None:
        print("construct _RunnerDecorator")
        self._roles = set()
        self._meta = meta
    @property
    def on_guest(self):
        print("add guest into role set")
        self._roles.add("guest")
        return self
    @property
    def on_host(self):
        print("add host into role set")
        self._roles.add("host")
        return self
    def __call__(self, cls):
        print(self)
        print(cls)
        return cls


class ComponentMeta:
    def __init__(self, name) -> None:
        print("construct component : " + name)
        self._name = name
    @property
    def bind_runner(self):
        return _RunnerDecorator(self)


hetero_lr_cpn_meta = ComponentMeta("HeteroLR")

@hetero_lr_cpn_meta.bind_runner.on_guest.on_host
def hetero_lr_runner_guest():
    print("execute hetero_lr_runner_guest") 

hetero_lr_runner_guest()
class Config:
    __controller_address= None
    __id = None
    __controller_port= None
    __display_timeout_value = None
    __resources= None

    def __init__(self, f):
        """Constructs the class and parses the configuration file and initialises the attributes values"""
        self.__CONFIG_FILE=f
        self.__configs= ["controller-address", "id", "controller-port", "display-timeout-value", "resources"]
        self.__functions =[self.__set_controller_address, self.__set_id, self.__set_controller_port, self.__set_display_timeout_value, self.__set_resources]
        self.parse()

    def parse(self):
        """Parses the CONFIG_FILE and initialises/updates the values of the corresponding attributes found in the file
            It's also  called by the constructor when an instance of the class is created"""
        r=open(self.__CONFIG_FILE,"r")
        lines = r.readlines()
        print("#######-Parsing configuration file-#######")
        for i in range(len(lines)):
            self.__process_line(lines[i], i)
        r.close()
        print(self)

    def __process_line(self, s, i):
        """Takes in a line and either processes it if it's unterpretable or ignores it if it's a comment or a blank line"""
        if s !="\n":
            c= s.split()[0]
            if c != "#":
                if c not in self.__configs:
                    print("Error in configuration file: Cannot understand line " + str(i+1))
                else:
                    i = self.__configs.index(c)
                    arg = s.split("=")[1].strip()
                    self.__functions[i](arg)

    """The following methods are used for setting the value of each attribute of the class. To be called by the process_line method"""
    def __set_controller_address(self, arg):
        self.__controller_address= arg
    def __set_id(self, arg):
        self.__id = arg
    def __set_controller_port(self, arg):
        self.__controller_port = arg
    def __set_display_timeout_value(self, arg):
        self.__display_timeout_value = arg
    def __set_resources(self,arg):
        self.__resources = arg

    """The following methods are accessors of the class"""
    def get_address(self):
        return self.__controller_address
    def get_port(self):
        return self.__controller_port
    def get_id(self):
        return self.__id
    def get_timeout(self):
        return self.__display_timeout_value
    def get_resources(self):
        return self.__resources
    def get_file(self):
        return self.__CONFIG_FILE

    def __str__(self):
        """"Format the state of the object into an easily readable format for debuging and easy visualisation"""
        s="#######-Current configuration-#######\n"
        s+="-Parsed file: " + str(self.__CONFIG_FILE) +"\n"
        s+="-Controller address: " + str(self.__controller_address) + "\n"
        s+="-Id: " + str(self.__id) +"\n"
        s+= "-Controller port: " + str(self.__controller_port) + "\n"
        s+= "-Display timeout value: " + str(self.__display_timeout_value) + "\n"
        s+= "-Resources directory: " + str(self.__resources) + "\n"
        s+= "#######--#######"
        return s

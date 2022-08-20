class efects
{
public:
    virtual ~efects() = default;
    virtual std::efects doAlgorithm(std::string_view data) const = 0;
};
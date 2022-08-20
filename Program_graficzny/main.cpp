#include <iostream>
#include <string>
class Efekt
{
public:
    virtual ~Efekt() = default;
    virtual std::string doAlgorithm(std::string_view data) const = 0;
};

/**
 * The BlackAndWhite defines the interface of interest to clients.
 */

class BlackAndWhite
{
 
private:
    std::unique_ptr<Efekt> strategy_;
    /**
     * Usually, the BlackAndWhite accepts a Efekt through the constructor, but also
     * provides a setter to change it at runtime.
     */
public:
    explicit BlackAndWhite(std::unique_ptr<Efekt>&& Efekt = {}) : strategy_(std::move(Efekt))
    {
    }
    /**
     * Usually, the BlackAndWhite allows replacing a Efekt object at runtime.
     */
    void set_strategy(std::unique_ptr<Efekt>&& Efekt)
    {
        strategy_ = std::move(Efekt);
    }
    /**
     * The BlackAndWhite delegates some work to the Efekt object instead of
     * implementing +multiple versions of the algorithm on its own.
     */
    void doSomeBusinessLogic() const
    {
        if (strategy_) {
            std::cout << "BlackAndWhite: Sorting data using the Efekt (not sure how it'll do it)\n";
            std::string result = strategy_->doAlgorithm("aecbd");
            std::cout << result << "\n";
        }
        else {
            std::cout << "BlackAndWhite: Efekt isn't set\n";
        }
    }
};

/**
 * Concrete Strategies implement the algorithm while following the base Efekt
 * interface. The interface makes them interchangeable in the BlackAndWhite.
 */
class ConcreteStrategyA : public Efekt
{
public:
    std::string doAlgorithm(std::string_view data) const override
    {
        std::string result(data);
        std::sort(std::begin(result), std::end(result));

        return result;
    }
};
class ConcreteStrategyB : public Efekt
{
    std::string doAlgorithm(std::string_view data) const override
    {
        std::string result(data);
        std::sort(std::begin(result), std::end(result), std::greater<>());

        return result;
    }
};
/**
 * The client code picks a concrete Efekt and passes it to the BlackAndWhite. The
 * client should be aware of the differences between strategies in order to make
 * the right choice.
 */

void clientCode()
{
    BlackAndWhite BlackAndWhite(std::make_unique<ConcreteStrategyA>());
    std::cout << "Client: Efekt is set to normal sorting.\n";
    BlackAndWhite.doSomeBusinessLogic();
    std::cout << "\n";
    std::cout << "Client: Efekt is set to reverse sorting.\n";
    BlackAndWhite.set_strategy(std::make_unique<ConcreteStrategyB>());
    BlackAndWhite.doSomeBusinessLogic();
}

int main()
{
    clientCode();
    return 0;
}
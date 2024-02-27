// Created by Camilo Castillo on 26/02/2024
// Adapter Pattern

#include <iostream>

//------------------------------------------------------------------------------

class Peg
{
    public:
        virtual float get() const = 0;
        virtual ~Peg() = default;
};

class RoundPeg : public Peg
{
    public:
        RoundPeg() = default;
        RoundPeg(float radius) : radius_(radius) {}
        float get() const override { return radius_; }
        ~RoundPeg() = default;

    private:
        float radius_;
};

class SquarePeg : public Peg
{
    public:
        SquarePeg() = default;
        SquarePeg(float width) : width_(width) {}
        float get() const override { return width_; }
        ~SquarePeg() = default;

    private:
        float width_;
};

//------------------------------------------------------------------------------

class Hole
{
    public:
        virtual float get() const = 0;
        virtual bool fits(Peg* peg) const = 0;
        virtual ~Hole() = default;
        
};

class RoundHole : public Hole
{
    public:
        RoundHole(float radius) : radius_(radius) {}
        float get() const override { return radius_; }
        bool fits(Peg* peg) const override { return peg->get() <= radius_; }
        ~RoundHole() = default;

    private:
        float radius_;
};

class SquareHole : public Hole
{
    public:
        SquareHole(float width) : width_(width) {}
        float get() const override { return width_; }
        bool fits(Peg* peg) const override { return peg->get() <= width_; }
        ~SquareHole() = default;

    private:
        float width_;
};

//------------------------------------------------------------------------------

class SquarePegAdapter : public RoundPeg
{
    public:
        SquarePegAdapter(SquarePeg* peg) : peg_(peg) {}
        float get() const override { return peg_->get() * 0.707; }
        ~SquarePegAdapter() = default;

    private:
        SquarePeg* peg_;
};

class RoundPegAdapter : public SquarePeg
{
    public:
        RoundPegAdapter(RoundPeg* peg) : peg_(peg) {}
        float get() const override { return peg_->get() / 0.707; }
        ~RoundPegAdapter() = default;

    private:
        RoundPeg* peg_;
};

//------------------------------------------------------------------------------

int main()
{
    // Holes
    RoundHole roundHole(5);
    SquareHole squareHole(5);

    // Pegs
    RoundPeg roundPeg(4);
    SquarePeg squarePeg(4);

    // Adapters
    SquarePegAdapter squarePegAdapter(&squarePeg);
    RoundPegAdapter roundPegAdapter(&roundPeg);

    // Fits 
    std::cout << "\nRound peg fits round hole: " << roundHole.fits(&roundPeg) << std::endl;
    std::cout << "Square peg fits square hole: " << squareHole.fits(&squarePeg) << std::endl;
    std::cout << "Square peg fits round hole: " << roundHole.fits(&squarePegAdapter) << std::endl;
    std::cout << "Round peg fits square hole: " << squareHole.fits(&roundPegAdapter) << std::endl;

    return 0;
}

//------------------------------------------------------------------------------

// classe base de pagamento
abstract class Pagamento {
    protected double valor;
    protected String descricao;
    
    public Pagamento(double valor, String descricao) {
        this.valor = valor;
        this.descricao = descricao;
    }
    
    // metodo abstrato pra processar
    public abstract void processar();
    
    // metodo pra calcular a taxa
    public abstract double getTaxa();
    
    public void mostrarInfo() {
        System.out.println("Descricao: " + descricao);
        System.out.println("Valor: R$" + valor);
        System.out.println("Taxa: R$" + getTaxa());
        System.out.println("Total: R$" + (valor + getTaxa()));
    }
}

// pagamento com cartao de credito
class CartaoCredito extends Pagamento {
    private String numCartao;
    private int parcelas;
    
    public CartaoCredito(double valor, String descricao, String numCartao, int parcelas) {
        super(valor, descricao);
        this.numCartao = numCartao;
        this.parcelas = parcelas;
    }
    
    public void processar() {
        System.out.println("\n--- Pagamento Cartao de Credito ---");
        mostrarInfo();
        System.out.println("Cartao: **** " + numCartao.substring(numCartao.length()-4));
        System.out.println("Parcelas: " + parcelas + "x");
        System.out.println("Aprovado!");
    }
    
    public double getTaxa() {
        // 3% + 1% por parcela extra
        return valor * (0.03 + (parcelas-1) * 0.01);
    }
}

// pagamento com debito
class CartaoDebito extends Pagamento {
    private String numCartao;
    
    public CartaoDebito(double valor, String descricao, String numCartao) {
        super(valor, descricao);
        this.numCartao = numCartao;
    }
    
    public void processar() {
        System.out.println("\n--- Pagamento Cartao de Debito ---");
        mostrarInfo();
        System.out.println("Cartao: **** " + numCartao.substring(numCartao.length()-4));
        System.out.println("Aprovado!");
    }
    
    public double getTaxa() {
        return valor * 0.015; // 1.5%
    }
}

// pagamento pix
class Pix extends Pagamento {
    private String chave;
    
    public Pix(double valor, String descricao, String chave) {
        super(valor, descricao);
        this.chave = chave;
    }
    
    public void processar() {
        System.out.println("\n--- Pagamento PIX ---");
        mostrarInfo();
        System.out.println("Chave: " + chave);
        System.out.println("Transferencia realizada!");
    }
    
    public double getTaxa() {
        return 0; // sem taxa
    }
}

// boleto bancario
class Boleto extends Pagamento {
    private String codBarras;
    private String vencimento;
    
    public Boleto(double valor, String descricao, String codBarras, String vencimento) {
        super(valor, descricao);
        this.codBarras = codBarras;
        this.vencimento = vencimento;
    }
    
    public void processar() {
        System.out.println("\n--- Boleto Bancario ---");
        mostrarInfo();
        System.out.println("Codigo: " + codBarras);
        System.out.println("Vencimento: " + vencimento);
        System.out.println("Boleto gerado");
    }
    
    public double getTaxa() {
        return 3.50; // taxa fixa
    }
}

// main
public class SistemaPagamentos {
    public static void main(String[] args) {
        
        // criando os pagamentos
        Pagamento p1 = new CartaoCredito(500, "Notebook", "1234567812345678", 3);
        Pagamento p2 = new CartaoDebito(150, "Teclado", "9876543298765432");
        Pagamento p3 = new Pix(80, "Mouse", "email@teste.com");
        Pagamento p4 = new Boleto(1200, "Monitor", "123456789", "15/12/2025");
        
        // processando
        System.out.println("=== SISTEMA DE PAGAMENTOS ===");
        
        p1.processar();
        p2.processar();
        p3.processar();
        p4.processar();
        
        // calculando total
        double total = p1.valor + p1.getTaxa() + 
                      p2.valor + p2.getTaxa() + 
                      p3.valor + p3.getTaxa() + 
                      p4.valor + p4.getTaxa();
        
        System.out.println("\n--- Resumo ---");
        System.out.println("Total geral: R$" + total);
    }
}

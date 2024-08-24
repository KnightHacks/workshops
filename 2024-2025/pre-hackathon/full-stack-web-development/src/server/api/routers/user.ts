import { users } from "~/server/db/schema";
import { createTRPCRouter, protectedProcedure } from "../trpc";
import { z } from "zod";
import { eq } from "drizzle-orm";

export const userRouter = createTRPCRouter({
  updateHandle: protectedProcedure
    .input(z.string())
    .mutation(async ({ ctx, input }) => {
      await ctx.db
        .update(users)
        .set({
          handle: input,
        })
        .where(eq(users.id, ctx.session.user.id));
    }),
});

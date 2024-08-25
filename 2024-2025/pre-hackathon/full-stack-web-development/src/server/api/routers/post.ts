import { posts } from "~/server/db/schema";
import { createTRPCRouter, protectedProcedure } from "../trpc";
import { z } from "zod";
import { desc, eq, isNull } from "drizzle-orm";

export const postRouter = createTRPCRouter({
  create: protectedProcedure
    .input(z.string())
    .mutation(async ({ ctx, input }) => {
      await ctx.db.insert(posts).values({
        userId: ctx.session.user.id,
        text: input,
      });
    }),
  reply: protectedProcedure
    .input(z.object({ text: z.string(), replyToId: z.number() }))
    .mutation(async ({ ctx, input }) => {
      await ctx.db.insert(posts).values({
        userId: ctx.session.user.id,
        text: input.text,
        postInReplyToId: input.replyToId,
      });
    }),
  delete: protectedProcedure
    .input(z.number())
    .mutation(async ({ ctx, input }) => {
      const postToDelete = await ctx.db.query.posts.findFirst({
        where: eq(posts.id, input),
      });

      if (!postToDelete || postToDelete.userId !== ctx.session.user.id) {
        return;
      }

      await ctx.db.delete(posts).where(eq(posts.id, input));
    }),
  update: protectedProcedure
    .input(z.object({ id: z.number(), text: z.string() }))
    .mutation(async ({ ctx, input }) => {
      const postToUpdate = await ctx.db.query.posts.findFirst({
        where: eq(posts.id, input.id),
      });

      if (!postToUpdate || postToUpdate.userId !== ctx.session.user.id) {
        return;
      }

      await ctx.db
        .update(posts)
        .set({
          text: input.text,
        })
        .where(eq(posts.id, input.id));
    }),
  all: protectedProcedure.query(async ({ ctx }) => {
    return await ctx.db.query.posts.findMany({
      orderBy: desc(posts.createdAt),
      with: {
        user: true,
      },
      where: isNull(posts.postInReplyToId),
    });
  }),
  allReplies: protectedProcedure
    .input(z.number())
    .query(async ({ ctx, input }) => {
      return await ctx.db.query.posts.findMany({
        where: eq(posts.postInReplyToId, input),
        orderBy: desc(posts.createdAt),
        with: {
          user: true,
          post: true,
        },
      });
    }),
});
